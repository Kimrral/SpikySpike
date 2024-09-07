// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "SSGameState.generated.h"

/**
 * 
 */
UCLASS()
class SPIKYSPIKE_API ASSGameState : public AGameState
{
	GENERATED_BODY()

public:
	ASSGameState();

protected:
	virtual void BeginPlay() override;

    virtual void PostInitializeComponents() override;

public:
    UPROPERTY(Replicated, BlueprintReadOnly, Category = "GameRule")
    float GameStartTime;

    // Function to handle ball touch
    UFUNCTION(BlueprintCallable, Category = "Score")
    void HandleBallTouch(AActor* InActor);

    // Function to get the score of a team
    UFUNCTION(BlueprintCallable, Category = "Score")
    int32 GetTeamScore(int32 TeamIndex) const;

    UFUNCTION(BlueprintCallable, Category = "Score")
    FORCEINLINE int32 GetScoredTeam() const { return ScoredTeam; };

	UFUNCTION(BlueprintCallable, Category = "Score")
    FORCEINLINE int32 GetRoundWinTeam() const { return RoundWinTeam; };

    void SetWinningTeamWhenRoundTimerEnd();

    // Function to get the winning team
    UFUNCTION(BlueprintCallable, Category = "Score")
    int32 GetWinningTeam() const;

    FTimerHandle RoundRestartTimerHandle;
    bool bEnableIncreaseScore;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GameRule")
    float RoundRestartTime;

private:
    // Scores for each team
    UPROPERTY(ReplicatedUsing = OnRep_TeamScores)
    TArray<int32> TeamScores;

    UPROPERTY(Replicated)
    int32 ScoredTeam;

    UPROPERTY(ReplicatedUsing = OnRep_RoundWinTeam)
    int32 RoundWinTeam;

    // Function to update the team scores
    UFUNCTION()
    void OnRep_TeamScores();

    UFUNCTION()
    void OnRep_RoundWinTeam();

    // Function to increment the score for a specific team
    void IncrementScore(int32 TeamIndex);
};
