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
}


