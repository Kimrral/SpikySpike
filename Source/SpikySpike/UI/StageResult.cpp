// Fill out your copyright notice in the Description page of Project Settings.


#include "SpikySpike/UI/StageResult.h"

#include "Components/WidgetSwitcher.h"
#include "Kismet/GameplayStatics.h"

void UStageResult::NativeConstruct()
{
	Super::NativeConstruct();

	WidgetSwitcher_StageResult->SetActiveWidgetIndex(0);
}

void UStageResult::FirstTeamWin() 
{
	WidgetSwitcher_StageResult->SetActiveWidgetIndex(0);
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UStageResult::ReturnToLobby, 5.f, false);
}

void UStageResult::SecondTeamWin() 
{
	WidgetSwitcher_StageResult->SetActiveWidgetIndex(1);
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UStageResult::ReturnToLobby, 5.f, false);
}

void UStageResult::ReturnToLobby()
{
	RemoveFromParent();
	const FName LobbyName = FName("LobbyLevel");
	UGameplayStatics::OpenLevel(GetWorld(), LobbyName, true);
}
