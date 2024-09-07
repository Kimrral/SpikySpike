// Fill out your copyright notice in the Description page of Project Settings.


#include "SSPlayerState.h"
#include "SSGameState.h"
#include "Components/TextBlock.h"
#include "SpikySpike/Player/SSPlayerController.h"
#include "SpikySpike/UI/ScoreBoard.h"

void ASSPlayerState::OnRep_TeamScores() const
{
	UpdateScoreUI();
}

void ASSPlayerState::OnRep_RoundWinTeam() const
{
	if (ASSPlayerController* PC = Cast<ASSPlayerController>(GetOwner()); PC && PC->IsLocalController())
	{
		if (const ASSGameState* SSGameState = PC->GetWorld()->GetGameState<ASSGameState>())
		{
			UE_LOG(LogTemp, Warning, TEXT("Result"))
			if (const int32 RoundWinTeam = SSGameState->GetRoundWinTeam(); RoundWinTeam == 1)
			{
				PC->StageResultOnViewport(0);
			}
			else
			{
				PC->StageResultOnViewport(1);
			}
		}
	}
}

void ASSPlayerState::OnRep_RoundEnd() const
{
	if (ASSPlayerController* PC = Cast<ASSPlayerController>(GetOwner()); PC && PC->IsLocalController())
	{
		// 라운드 종료시 페이드 인 / 페이드 아웃 로직
	}
}

void ASSPlayerState::UpdateScoreUI() const
{
	if (const ASSPlayerController* PC = Cast<ASSPlayerController>(GetOwner()); PC && PC->IsLocalController())
	{
		if (const ASSGameState* SSGameState = PC->GetWorld()->GetGameState<ASSGameState>())
		{
			if (IsValid(PC->ScoreBoard))
			{
				if (const int32 ScoredTeam = SSGameState->GetScoredTeam(); ScoredTeam == 1)
				{
					PC->ScoreBoard->FirstTeamScoreNumber++;
					PC->ScoreBoard->FirstTeamScore->SetText(FText::AsNumber(PC->ScoreBoard->FirstTeamScoreNumber));
				}
				else if (ScoredTeam == 0)
				{
					PC->ScoreBoard->SecondTeamScoreNumber++;
					PC->ScoreBoard->SecondTeamScore->SetText(FText::AsNumber(PC->ScoreBoard->SecondTeamScoreNumber));
				}
			}
		}
	}
}
