// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "SSGameMode.generated.h"

class ASSPlayerState;

UCLASS(minimalapi)
class ASSGameMode : public AGameMode
{
	GENERATED_BODY()

public:
    ASSGameMode();

protected:
    virtual void BeginPlay() override;

    virtual void PostLogin(APlayerController* NewPlayer) override;
};


