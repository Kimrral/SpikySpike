// Fill out your copyright notice in the Description page of Project Settings.


#include "SpikySpike/Player/SSPlayerController.h"

#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "SpikySpike/UI/ScoreBoard.h"
#include "SpikySpike/UI/StageResult.h"

void ASSPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ScoreBoardOnViewport();

	if (APlayerCameraManager* const CameraManager = Cast<APlayerCameraManager>(
		UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)))
	{
		CameraManager->StopCameraFade();
		CameraManager->StartCameraFade(1.0, 0, 20.0, FColor::Black, false, false);
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

void ASSPlayerController::StageResultOnViewport(const int32 WinnerNumber)
{
	if (IsValid(StageResultWidget) && IsLocalController())
	{
		// 위젯 생성
		StageResult = CreateWidget<UStageResult>(this, StageResultWidget);
		if (IsValid(StageResultWidget))
		{
			// 뷰포트에 위젯 추가
			StageResult->AddToViewport();
		}
	}

	UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(this);
	SetShowMouseCursor(true);

	if (WinnerNumber == 0)
	{
		StageResult->FirstTeamWin();
	}
	else
	{
		StageResult->SecondTeamWin();
	}
}

void ASSPlayerController::SetViewTargetClient_Implementation()
{
	AActor* CameraActor = GetWorld()->SpawnActor(CameraActorClass);
	SetViewTarget(CameraActor);
}
