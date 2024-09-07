// Fill out your copyright notice in the Description page of Project Settings.

#include "SpikySpike/UI/ScoreBoard.h"
#include "Components/TextBlock.h"
#include "Kismet/KismetStringLibrary.h"
#include "SpikySpike/GameMode/SSGameState.h"

void UScoreBoard::NativeConstruct()
{
	Super::NativeConstruct();

	// CountdownConstruct 애니메이션을 재생합니다.
	PlayAnimation(CountdownConstruct);

	FirstTeamScore->SetText(FText::AsNumber(FirstTeamScoreNumber));
	SecondTeamScore->SetText(FText::AsNumber(SecondTeamScoreNumber));

}

void UScoreBoard::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	SetCountdownTimer(InDeltaTime);
}

void UScoreBoard::SetCountdownTimer(float InDeltaTime)
{
	// // Countdown 값을 현재 프레임의 델타 시간만큼 감소시킵니다.
	// // FMath::Clamp 함수를 사용하여 Countdown 값을 0.f에서 maxvalue 사이로 제한합니다.
	// Countdown = FMath::Clamp(Countdown -= GetWorld()->GetGameState()->GetServerWorldTimeSeconds(), 0.f, Countdown);
	//
	// // Countdown 값을 문자열로 변환합니다.
	// const FString CountdownString = UKismetStringLibrary::TimeSecondsToString(Countdown);
 //    
	// // 변환된 문자열을 CountdownValue 텍스트 위젯에 설정합니다.
	// CountdownValue->SetText(FText::FromString(CountdownString));

	// Countdown 값을 현재 프레임의 델타 시간(InDeltaTime)만큼 감소시킵니다.
	//Countdown = FMath::Clamp(Countdown - GetWorld()->GetDeltaSeconds(), 0.f, Countdown);

	// GameState에서 StartTime을 가져옴
    ASSGameState* SSGameState = GetWorld()->GetGameState<ASSGameState>();
    if (!SSGameState) 
    {
    	return;
	}

    // 현재 시간을 계산하여 Countdown을 업데이트
	const float ElapsedTime = GetWorld()->GetTimeSeconds() - SSGameState->GameStartTime;
    // 총 라운드 시간에서 경과된 시간을 빼서 남은 시간을 계산
	const float RemainingTime = FMath::Clamp(Countdown - ElapsedTime, 0.f, Countdown);

	// Countdown 값을 문자열로 변환합니다.
	const FString CountdownString = UKismetStringLibrary::TimeSecondsToString(RemainingTime);
    
	// 변환된 문자열을 CountdownValue 텍스트 위젯에 설정합니다.
	CountdownValue->SetText(FText::FromString(CountdownString));
}
