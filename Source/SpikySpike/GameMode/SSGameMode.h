// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SSGameMode.generated.h"

class ASSPlayerState;

UCLASS(minimalapi)
class ASSGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
    ASSGameMode();

protected:
    virtual void BeginPlay() override;

    virtual void PostLogin(APlayerController* NewPlayer) override;
};


