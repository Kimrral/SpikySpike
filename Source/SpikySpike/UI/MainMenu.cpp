// Fill out your copyright notice in the Description page of Project Settings.


#include "SpikySpike/UI/MainMenu.h"

#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "SpikySpike/Player/SSLobbyController.h"
#include "SpikySpike/Player/SSPlayerController.h"

void UMainMenu::NativeConstruct()
{
	Super::NativeConstruct();

	Controller = Cast<ASSLobbyController>(GetWorld()->GetFirstPlayerController());

	WidgetSwitcher_MainMenu->SetActiveWidgetIndex(0);

	Btn_GameStart->OnPressed.AddDynamic(this, &UMainMenu::StartGame);
	Btn_QuitGame->OnPressed.AddDynamic(this, &UMainMenu::QuitGame);
	Btn_QuitYes->OnPressed.AddDynamic(this, &UMainMenu::QuitYes);
	Btn_QuitNo->OnPressed.AddDynamic(this, &UMainMenu::QuitNo);

	PlayAnimation(MainMenuAppearAnimation);
}

void UMainMenu::StartGame()
{
	if (APlayerCameraManager* const CameraManager = Cast<APlayerCameraManager>(UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)))
	{
		CameraManager->StartCameraFade(0, 1, 1.5, FColor::Black, false, false);
		PlayAnimation(MainMenuDisappearAnimation);
	}

	OpenDedicatedServer();
}

void UMainMenu::QuitGame()
{
	// Switch To Ask Quit Game
	WidgetSwitcher_MainMenu->SetActiveWidgetIndex(1);
}

void UMainMenu::QuitYes()
{
	UE_LOG(LogTemp, Warning, TEXT("QuitYes"))
	if (IsValid(Controller))
	{
		UKismetSystemLibrary::QuitGame(GetWorld(), Controller, EQuitPreference::Quit, true);
	}
}

void UMainMenu::QuitNo()
{
	WidgetSwitcher_MainMenu->SetActiveWidgetIndex(0);
}
