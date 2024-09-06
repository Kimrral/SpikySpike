// Copyright Epic Games, Inc. All Rights Reserved.

#include "SSGameMode.h"

#include "Net/UnrealNetwork.h"
#include "UObject/ConstructorHelpers.h"

ASSGameMode::ASSGameMode()
{
    // Initialize scores for two teams
    TeamScores.SetNum(2);
    TeamScores[0] = 0; // Team 0
    TeamScores[1] = 0; // Team 1

    // Ensure the game mode replicates
    bReplicates = true;
}

void ASSGameMode::BeginPlay()
{
    Super::BeginPlay();

    // Optionally spawn scoring volumes or set up other game elements here
}

void ASSGameMode::HandleBallTouch(FVector BallLocation)
{
    // Determine which team should score based on ball location
    int32 TeamIndex = 0; // Determine team index based on ball location
    if (IsBallInScoringArea(BallLocation, TeamIndex))
    {
        IncrementScore(TeamIndex);
    }
}

void ASSGameMode::IncrementScore(int32 TeamIndex)
{
    if (TeamIndex >= 0 && TeamIndex < TeamScores.Num())
    {
        TeamScores[TeamIndex]++;
        OnRep_TeamScores();
    }
}

bool ASSGameMode::IsBallInScoringArea(FVector BallLocation, int32 TeamIndex)
{
    // Implement logic to check if ball is in scoring area based on team index
    // For simplicity, use placeholders
    return true;
}

int32 ASSGameMode::GetTeamScore(int32 TeamIndex) const
{
    if (TeamIndex >= 0 && TeamIndex < TeamScores.Num())
    {
        return TeamScores[TeamIndex];
    }
    return 0;
}

int32 ASSGameMode::GetWinningTeam() const
{
    if (TeamScores[0] > TeamScores[1])
    {
        return 0;
    }
    else if (TeamScores[1] > TeamScores[0])
    {
        return 1;
    }
    return -1; // Tie
}

void ASSGameMode::OnRep_TeamScores()
{
    // Handle score replication updates (optional, if you need specific behavior)
}

void ASSGameMode::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ASSGameMode, TeamScores);
}