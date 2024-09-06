// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SSGameMode.generated.h"

UCLASS(minimalapi)
class ASSGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
    ASSGameMode();

protected:
    virtual void BeginPlay() override;

public:
    // Function to handle ball touch
    UFUNCTION(BlueprintCallable, Category = "Score")
    void HandleBallTouch(FVector BallLocation);

    // Function to get the score of a team
    UFUNCTION(BlueprintCallable, Category = "Score")
    int32 GetTeamScore(int32 TeamIndex) const;

    // Function to get the winning team
    UFUNCTION(BlueprintCallable, Category = "Score")
    int32 GetWinningTeam() const;

private:
    // Scores for each team
    UPROPERTY(ReplicatedUsing = OnRep_TeamScores)
    TArray<int32> TeamScores;

    // Function to update the team scores
    UFUNCTION()
    void OnRep_TeamScores();

    // Function to increment the score for a specific team
    void IncrementScore(int32 TeamIndex);

    // Boundaries for scoring (e.g., the volume)
    UPROPERTY(EditAnywhere, Category = "Gameplay")
    TObjectPtr<AVolume> ScoringVolume;

    // Function to check if a ball is in the scoring area
	static bool IsBallInScoringArea(FVector BallLocation, int32 TeamIndex);
};


