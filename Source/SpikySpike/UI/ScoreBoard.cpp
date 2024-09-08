// Fill out your copyright notice in the Description page of Project Settings.

#include "SpikySpike/UI/ScoreBoard.h"
#include "Components/TextBlock.h"

void UScoreBoard::NativeConstruct()
{
	Super::NativeConstruct();

	FirstTeamScore->SetText(FText::AsNumber(FirstTeamScoreNumber));
	SecondTeamScore->SetText(FText::AsNumber(SecondTeamScoreNumber));
}
