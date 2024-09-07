// Copyright Epic Games, Inc. All Rights Reserved.

#include "SSGameMode.h"
#include "SSGameState.h"
#include "SSPlayerState.h"
#include "GameFramework/PawnMovementComponent.h"
#include "SpikySpike/Ball/SSVolleyBall.h"
#include "UObject/ConstructorHelpers.h"

ASSGameMode::ASSGameMode()
{
	PlayerStateClass = ASSPlayerState::StaticClass();
	GameStateClass = ASSGameState::StaticClass();
	VolleyBallClass = ASSVolleyBall::StaticClass();

	GoalScore = 3;
	RoundTimeSeconds = 60.f;
	BallSpawnLocation = FVector(870.000000, 570.000000, 850.000000);
}

void ASSGameMode::RestartMatch()
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
}

void ASSGameMode::EndMatch()
{
	UE_LOG(LogTemp, Warning, TEXT("Ending The Game"));

	ASSGameState* SSGameState = GetGameState<ASSGameState>();
	if (SSGameState)
	{
		const int32 WinningTeam = SSGameState->GetWinningTeam();
	}

	SSVolleyBall->Destroy(true);

	Super::EndMatch();
}

void ASSGameMode::BeginPlay()
{
    Super::BeginPlay();

	if (VolleyBallClass)
	{
		SSVolleyBall = GetWorld()->SpawnActor<ASSVolleyBall>(VolleyBallClass, BallSpawnLocation, FRotator::ZeroRotator);
	}
}

void ASSGameMode::StartMatch()
{
	Super::StartMatch();

	if (RoundTimeSeconds > 0)
	{
		GetWorldTimerManager().SetTimer(RoundTimerHandle, this, &ASSGameMode::EndMatch, RoundTimeSeconds, false);
	}
}

void ASSGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	ASSPlayerState* SSPlayerState = Cast<ASSPlayerState>(NewPlayer->PlayerState);
	if (SSPlayerState)
	{
		SSPlayerState->SetTeamID(NumPlayers % 2);
	}
}
