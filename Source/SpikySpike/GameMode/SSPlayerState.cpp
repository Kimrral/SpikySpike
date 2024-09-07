// Fill out your copyright notice in the Description page of Project Settings.


#include "SSPlayerState.h"

#include "SSGameState.h"
#include "Components/TextBlock.h"
#include "SpikySpike/Player/SSPlayerController.h"
#include "SpikySpike/UI/ScoreBoard.h"

ASSPlayerState::ASSPlayerState()
{
}

void ASSPlayerState::OnRep_TeamScores() const
{
	UpdateScoreUI();
}

void ASSPlayerState::UpdateScoreUI() const
{
	if (const ASSPlayerController* PC = Cast<ASSPlayerController>(GetOwner()); PC && PC->IsLocalController())
	{
		if (const ASSGameState* SSGameState = PC->GetWorld()->GetGameState<ASSGameState>())
		{
			if (IsValid(PC->ScoreBoard))
			{
				if (const int32 ScoredTeam = SSGameState->GetScoredTeam(); ScoredTeam == 0)
				{
					PC->ScoreBoard->FirstTeamScoreNumber++;
					PC->ScoreBoard->FirstTeamScore->SetText(FText::AsNumber(PC->ScoreBoard->FirstTeamScoreNumber));
				}
				else
				{
					PC->ScoreBoard->SecondTeamScoreNumber++;
					PC->ScoreBoard->SecondTeamScore->SetText(FText::AsNumber(PC->ScoreBoard->SecondTeamScoreNumber));
				}
			}
		}
	}
}
