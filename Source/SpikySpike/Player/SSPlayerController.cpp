// Fill out your copyright notice in the Description page of Project Settings.


#include "SpikySpike/Player/SSPlayerController.h"

#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "SpikySpike/UI/ScoreBoard.h"

void ASSPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(MainMenuWidget) && IsLocalController())
	{
		// 위젯 생성
		if (UUserWidget* WidgetInstance = CreateWidget<UUserWidget>(this, MainMenuWidget); IsValid(WidgetInstance))
		{
			// 뷰포트에 위젯 추가
			WidgetInstance->AddToViewport();
		}
	}

	UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(this);  
	SetShowMouseCursor(true); 
}

void ASSPlayerController::ScoreBoardOnViewport()
{
	if (IsValid(ScoreBoardWidget) && IsLocalController())
	{
		// 위젯 생성
		ScoreBoard = CreateWidget<UScoreBoard>(this, ScoreBoardWidget);
		if (IsValid(ScoreBoard))
		{
			// 뷰포트에 위젯 추가
			ScoreBoard->AddToViewport();
		}
	}
	
	UWidgetBlueprintLibrary::SetInputMode_GameOnly(this);  
	SetShowMouseCursor(false); 
}
