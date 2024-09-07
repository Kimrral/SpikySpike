// Fill out your copyright notice in the Description page of Project Settings.


#include "SpikySpike/Player/SSPlayerController.h"

#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

void ASSPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(MainMenuWidget) && IsLocalController())
	{
		// 위젯 생성
		if (UUserWidget* WidgetInstance = CreateWidget<UUserWidget>(this, MainMenuWidget))
		{
			// 뷰포트에 위젯 추가
			WidgetInstance->AddToViewport();
		}
	}

	UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(this);  
	SetShowMouseCursor(true); 
}
