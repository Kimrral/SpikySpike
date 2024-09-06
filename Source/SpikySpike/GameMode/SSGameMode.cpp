// Copyright Epic Games, Inc. All Rights Reserved.

#include "SSGameMode.h"
#include "Net/UnrealNetwork.h"
#include "UObject/ConstructorHelpers.h"

ASSGameMode::ASSGameMode()
{
}

void ASSGameMode::BeginPlay()
{
    Super::BeginPlay();

}

void ASSGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	
}
