// Fill out your copyright notice in the Description page of Project Settings.


#include "SpikySpike/UI/ScoreBoard.h"

#include "Components/TextBlock.h"
#include "GameFramework/GameStateBase.h"
#include "Kismet/KismetStringLibrary.h"

void UScoreBoard::NativeConstruct()
{
	Super::NativeConstruct();

	// CountdownConstruct 애니메이션을 재생합니다.
	PlayAnimation(CountdownConstruct);
}

void UScoreBoard::NativeTick(const FGeometry& MyGeometry, const float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	SetCountdownTimer();
}

void UScoreBoard::SetCountdownTimer()
{
	// Countdown 값을 현재 프레임의 델타 시간만큼 감소시킵니다.
	// FMath::Clamp 함수를 사용하여 Countdown 값을 0.f에서 maxvalue 사이로 제한합니다.
	Countdown = FMath::Clamp(Countdown -= GetWorld()->GetGameState()->GetServerWorldTimeSeconds(), 0.f, Countdown);

	// Countdown 값을 문자열로 변환합니다.
	const FString CountdownString = UKismetStringLibrary::TimeSecondsToString(Countdown);
    
	// 변환된 문자열을 CountdownValue 텍스트 위젯에 설정합니다.
	CountdownValue->SetText(FText::FromString(CountdownString));
}
