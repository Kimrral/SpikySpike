// Fill out your copyright notice in the Description page of Project Settings.


#include "SSPlayerState.h"

#include "SSGameState.h"

ASSPlayerState::ASSPlayerState()
{

}

void ASSPlayerState::OnRep_TeamScores()
{
	UpdateScoreUI();
}

void ASSPlayerState::UpdateScoreUI()
{
	if (GetNetMode() == NM_DedicatedServer)
	{
		return;
	}

	APlayerController* PC = Cast<APlayerController>(GetOwner());
	if (PC && PC->IsLocalController())
	{
		ASSGameState* SSGameState = PC->GetWorld()->GetGameState<ASSGameState>();
		if (SSGameState)
		{
			const int32 ScoredTeam = SSGameState->GetScoredTeam();
			if (TeamID == ScoredTeam)
			{
				
			}
			else
			{
				
			}
		}
	}
}
