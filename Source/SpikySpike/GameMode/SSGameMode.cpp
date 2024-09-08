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
	BallSpawnLocation = FVector(870.000000, 570.000000, 850.000000);
}

void ASSGameMode::StartRound()
{
	UE_LOG(LogTemp, Warning, TEXT("Restarting The Game"));

	// 플레이어 트랜스폼 및 움직임 초기화
	int32 CurIndex = 0;
	for (const auto PlayerState : GameState->PlayerArray)
	{
		APlayerController* PlayerController = PlayerState->GetPlayerController();
		if (PlayerController && PlayerController->GetPawn())
		{
			const FString PlayerStartTag = FString::Printf(TEXT("PlayerStart%d"), CurIndex);
			const AActor* PlayerStart = FindPlayerStart(PlayerController, PlayerStartTag);
			if (PlayerStart)
			{
				APawn* Pawn = PlayerController->GetPawn();
				Pawn->SetActorLocation(PlayerStart->GetActorLocation());
				Pawn->SetActorRotation(PlayerStart->GetActorRotation());

				Pawn->GetMovementComponent()->StopMovementImmediately();
			}

			ASSPlayerController* SSPlayerController = Cast<ASSPlayerController>(PlayerController);
			SSPlayerController->SetViewTargetClient();

			++CurIndex;
		}
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

	ASSGameState* SSGameState = GetGameState<ASSGameState>();
	if (SSGameState)
	{
		SSGameState->bEnableIncreaseScore = true;
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

	// Destroy Player
	for (const auto PlayerState : GameState->PlayerArray)
	{
		APlayerController* PC = PlayerState->GetPlayerController();
		if (PC)
		{
			APawn* PlayerPawn = PC->GetPawn();
			if (PlayerPawn)
			{
				PlayerPawn->Destroy(true);
			}
		}
	}

	// Destroy Ball
	SSVolleyBall->Destroy(true);

	GetWorldTimerManager().ClearAllTimersForObject(this);
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
		GetWorldTimerManager().SetTimer(StartTimerHandle, this, &ASSGameMode::StartRound, 2.0f, false);
	}
}
