// Copyright Epic Games, Inc. All Rights Reserved.

#include "SSGameMode.h"
#include "SSGameState.h"
#include "SSPlayerState.h"
#include "UObject/ConstructorHelpers.h"

ASSGameMode::ASSGameMode()
{
	PlayerStateClass = ASSPlayerState::StaticClass();
	GameStateClass = ASSGameState::StaticClass();
}

void ASSGameMode::BeginPlay()
{
    Super::BeginPlay();

}

void ASSGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	
}
