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
	ASSPlayerState();

	FORCEINLINE int32 GetTeamID() const { return TeamID; }

	FORCEINLINE void SetTeamID(const int32 InTeamID) { TeamID = InTeamID; }

	UFUNCTION()
	void OnRep_TeamScores();

private:
	// Team ID for this player
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Team", meta = (AllowPrivateAccess = "true"))
    int32 TeamID = -1;
};
