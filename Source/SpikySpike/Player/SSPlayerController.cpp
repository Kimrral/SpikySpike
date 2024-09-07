// Fill out your copyright notice in the Description page of Project Settings.


#include "SpikySpike/Player/SSPlayerController.h"

#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "SpikySpike/UI/ScoreBoard.h"

void ASSPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ScoreBoardOnViewport();

	if (APlayerCameraManager* const CameraManager = Cast<APlayerCameraManager>(UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)))
	{
		CameraManager->StartCameraFade(1, 0, 2.0, FColor::Black, false, false);
	}
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
