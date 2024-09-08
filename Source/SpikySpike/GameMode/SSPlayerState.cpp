// Fill out your copyright notice in the Description page of Project Settings.


#include "SSPlayerState.h"
#include "SSGameState.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
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

void ASSPlayerState::OnRep_RoundEnd()
{
	if (const ASSPlayerController* PC = Cast<ASSPlayerController>(GetOwner()); PC && PC->IsLocalController())
	{
		UE_LOG(LogTemp, Warning, TEXT("Round End"))
		ProcessCameraFade();
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

void ASSPlayerState::ProcessCameraFade() const
{
	// 라운드 종료시 페이드 인 / 페이드 아웃 로직
	if (APlayerCameraManager* const CameraManager = Cast<APlayerCameraManager>(
		UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)))
	{
		CameraManager->StopCameraFade();
		CameraManager->StartCameraFade(0, 1, 3.f, FColor::Black, false, false);

		// 페이드 인이 끝나는 2초 후에 페이드 아웃 시작
		FTimerHandle TimerHandle;
		FTimerDelegate TimerDelegate;
		TimerDelegate.BindLambda([CameraManager]() // CameraManager를 람다 내에서 안전하게 사용
		{
			if (CameraManager) // CameraManager가 유효한지 확인
			{
				CameraManager->StopCameraFade();
				CameraManager->StartCameraFade(1.0, 0, 3.f, FColor::Black, false, false);
			}
		});

		// 타이머가 페이드 인 시간 후에 실행되도록 설정
		GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, 3.f, false);
	}
}
