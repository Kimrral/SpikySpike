// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SSPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class SPIKYSPIKE_API ASSPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	void OnRep_TeamScores() const;

	void OnRep_RoundWinTeam() const;

	void UpdateScoreUI() const;
};
