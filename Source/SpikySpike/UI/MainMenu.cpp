// Fill out your copyright notice in the Description page of Project Settings.


#include "SpikySpike/UI/MainMenu.h"

#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Kismet/KismetSystemLibrary.h"

void UMainMenu::NativeConstruct()
{
	Super::NativeConstruct();

	Controller = Cast<APlayerController>(GetWorld()->GetFirstPlayerController());

	WidgetSwitcher_MainMenu->SetActiveWidgetIndex(0);

	Btn_GameStart->OnPressed.AddDynamic(this, &UMainMenu::StartGame);
	Btn_GameStart->OnPressed.AddDynamic(this, &UMainMenu::QuitGame);
}

void UMainMenu::StartGame()
{

}

void UMainMenu::QuitGame()
{
	// Switch To Ask Quit Game
	WidgetSwitcher_MainMenu->SetActiveWidgetIndex(1);
}

void UMainMenu::QuitYes() const
{
	if(IsValid(Controller))
	{
		const TEnumAsByte<EQuitPreference::Type> Types = EQuitPreference::Quit;
		UKismetSystemLibrary::QuitGame(GetWorld(), Controller, Types, false);
	}	
}

void UMainMenu::QuitNo() const
{
	if(IsValid(Controller))
	{
		WidgetSwitcher_MainMenu->SetActiveWidgetIndex(0);
	}	
}
