// Copyright Epic Games, Inc. All Rights Reserved.

#include "SSGameMode.h"
#include "SSGameState.h"
#include "SSPlayerState.h"
#include "SpikySpike/Player/SSPlayerController.h"
#include "GameFramework/PawnMovementComponent.h"
#include "SpikySpike/Ball/SSVolleyBall.h"
#include "UObject/ConstructorHelpers.h"

ASSGameMode::ASSGameMode()
{
	PlayerStateClass = ASSPlayerState::StaticClass();
	GameStateClass = ASSGameState::StaticClass();
	VolleyBallClass = ASSVolleyBall::StaticClass();

	GoalScore = 3;
	MinNumPlayer = 2;
	RoundTimeSeconds = 60.f;
	BallSpawnLocation = FVector(870.000000, 570.000000, 850.000000);
}

void ASSGameMode::StartRound()
{
	UE_LOG(LogTemp, Warning, TEXT("Restarting The Game"));

	// 플레이어 트랜스폼 및 움직임 초기화
	for (const auto PlayerState : GameState->PlayerArray)
	{
		APlayerController* PlayerController = PlayerState->GetPlayerController();
		if (PlayerController && PlayerController->GetPawn())
		{
			const AActor* PlayerStart = FindPlayerStart(PlayerController);
			if (PlayerStart)
			{
				APawn* Pawn = PlayerController->GetPawn();
				Pawn->SetActorLocation(PlayerStart->GetActorLocation());
				Pawn->SetActorRotation(PlayerStart->GetActorRotation());

				Pawn->GetMovementComponent()->StopMovementImmediately();
			}

			ASSPlayerController* SSPlayerController = Cast<ASSPlayerController>(PlayerController);
			SSPlayerController->SetViewTargetClient();
		}
	}

	// 공 위치 및 움직임 초기화
	SSVolleyBall->SetActorLocation(BallSpawnLocation);

	UPrimitiveComponent* BallRootComponent = Cast<UPrimitiveComponent>(SSVolleyBall->GetRootComponent());
    if (BallRootComponent)
    {
        BallRootComponent->SetPhysicsLinearVelocity(FVector::ZeroVector);  // 속도 초기화
        BallRootComponent->SetPhysicsAngularVelocityInDegrees(FVector::ZeroVector);  // 회전 초기화
    }

	// 공 위치 및 움직임 초기화
	if (SSVolleyBall)
	{
		SSVolleyBall->SetActorLocation(BallSpawnLocation);

		if (SSVolleyBall->BallMesh)
		{
			SSVolleyBall->BallMesh->SetPhysicsLinearVelocity(FVector::ZeroVector);  // 속도 초기화
	        SSVolleyBall->BallMesh->SetPhysicsAngularVelocityInDegrees(FVector::ZeroVector);  // 회전 초기화
			SSVolleyBall->BallMesh->SetSimulatePhysics(true);
		}
	}
}

void ASSGameMode::EndRound() const
{
	if (!GetWorldTimerManager().IsTimerActive(RoundTimerHandle))
	{
		ASSGameState* SSGameState = GetGameState<ASSGameState>();
		if (SSGameState)
		{
			SSGameState->SetWinningTeamWhenRoundTimerEnd();
		}
	}

	SSVolleyBall->Destroy(true);
}

void ASSGameMode::BeginPlay()
{
    Super::BeginPlay();

	if (VolleyBallClass)
	{
		SSVolleyBall = GetWorld()->SpawnActor<ASSVolleyBall>(VolleyBallClass, BallSpawnLocation, FRotator::ZeroRotator);
		if (SSVolleyBall && SSVolleyBall->BallMesh)
		{
			SSVolleyBall->BallMesh->SetSimulatePhysics(false);
		}
	}
}

void ASSGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if (GetNetMode() == NM_Standalone || NumPlayers == MinNumPlayer)
	{
		ASSGameState* SSGameState = GetGameState<ASSGameState>();
		if (SSGameState)
		{
			SSGameState->GameStartTime = GetWorld()->GetTimeSeconds();
		}

		if (RoundTimeSeconds > 0)
		{
			GetWorldTimerManager().SetTimer(RoundTimerHandle, this, &ASSGameMode::EndRound, RoundTimeSeconds, false);
		}

		GetWorldTimerManager().SetTimer(StartTimerHandle, this, &ASSGameMode::StartRound, 2.0f, false);
	}
}
