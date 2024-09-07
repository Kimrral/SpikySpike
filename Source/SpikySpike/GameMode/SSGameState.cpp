// Fill out your copyright notice in the Description page of Project Settings.

#include "SSGameState.h"

#include "SSGameMode.h"
#include "SSPlayerState.h"
#include "Net/UnrealNetwork.h"

ASSGameState::ASSGameState()
{
    // Initialize scores for two teams
    TeamScores.SetNum(2);
    TeamScores[0] = 0; // Team 0
    TeamScores[1] = 0; // Team 1

    ScoredTeam = -1;
    RoundWinTeam = -1;
    GameStartTime = 0.f;

    // Ensure the game mode replicates
    bReplicates = true;
}

void ASSGameState::BeginPlay()
{
    Super::BeginPlay();

    // Optionally spawn scoring volumes or set up other game elements here
}

void ASSGameState::PostInitializeComponents()
{
	Super::PostInitializeComponents();

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
    if (!HasAuthority())
    {
	    return;
    }

    if (TeamIndex >= 0 && TeamIndex < TeamScores.Num())
    {
        ScoredTeam = TeamIndex;
        TeamScores[ScoredTeam]++;

        if (HasAuthority())
        {
	        OnRep_TeamScores();
        }

    	UE_LOG(LogTemp, Warning, TEXT("Team %d Scores, Total Score : %d"), ScoredTeam, GetTeamScore(ScoredTeam));

        ASSGameMode* SSGameMode = GetWorld()->GetAuthGameMode<ASSGameMode>();
        if (SSGameMode)
        {
	        if (GetTeamScore(ScoredTeam) == SSGameMode->GetGoalScore())
	        {
                RoundWinTeam = ScoredTeam;
		        SSGameMode->EndRound();
	        }
            else
            {
	            SSGameMode->StartRound();
            }
        }
    }
}

int32 ASSGameState::GetTeamScore(const int32 TeamIndex) const
{
    if (TeamIndex >= 0 && TeamIndex < TeamScores.Num())
    {
        return TeamScores[TeamIndex];
    }

    return 0;
}

void ASSGameState::SetWinningTeamWhenRoundTimerEnd()
{
    RoundWinTeam = GetWinningTeam();
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
    for (APlayerState* PlayerState : PlayerArray)
    {
        ASSPlayerState* SSPlayerState = Cast<ASSPlayerState>(PlayerState);
	    if (SSPlayerState)
	    {
		    SSPlayerState->OnRep_TeamScores();
	    }
    }
}

void ASSGameState::OnRep_RoundWinTeam()
{
	for (auto PlayerState : PlayerArray)
	{
	    ASSPlayerState* SSPlayerState = Cast<ASSPlayerState>(PlayerState);
        if (SSPlayerState)
	    {
	        SSPlayerState->OnRep_RoundWinTeam();
	    }
	}
}

void ASSGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ASSGameState, TeamScores);
    DOREPLIFETIME(ASSGameState, ScoredTeam);
    DOREPLIFETIME(ASSGameState, GameStartTime);
}
