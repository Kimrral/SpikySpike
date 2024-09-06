// Fill out your copyright notice in the Description page of Project Settings.


#include "SSGameState.h"
#include "Net/UnrealNetwork.h"

ASSGameState::ASSGameState()
{
    // Initialize scores for two teams
    TeamScores.SetNum(2);
    TeamScores[0] = 0; // Team 0
    TeamScores[1] = 0; // Team 1

    // Ensure the game mode replicates
    bReplicates = true;
}

void ASSGameState::BeginPlay()
{
    Super::BeginPlay();

    // Optionally spawn scoring volumes or set up other game elements here
}

void ASSGameState::HandleBallTouch(AActor* InActor)
{
    if (InActor && InActor->ActorHasTag("Floor"))
    {
	    IncrementScore(InActor->ActorHasTag("A") ? 0 : 1);
    }
}

void ASSGameState::IncrementScore(const int32 TeamIndex)
{
    if (TeamIndex >= 0 && TeamIndex < TeamScores.Num())
    {
        TeamScores[TeamIndex]++;
        OnRep_TeamScores();
    }
}

int32 ASSGameState::GetTeamScore(int32 TeamIndex) const
{
    if (TeamIndex >= 0 && TeamIndex < TeamScores.Num())
    {
        return TeamScores[TeamIndex];
    }

    return 0;
}

int32 ASSGameState::GetWinningTeam() const
{
    if (TeamScores[0] > TeamScores[1])
    {
        return 0;
    }

	if (TeamScores[1] > TeamScores[0])
    {
        return 1;
    }

	return -1; // Tie
}

void ASSGameState::OnRep_TeamScores()
{
    // Handle score replication updates (optional, if you need specific behavior)
    UE_LOG(LogTemp, Warning, TEXT("Team %d Scores, Total Score : %d"), 0, 1);
}

void ASSGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ASSGameState, TeamScores);
}