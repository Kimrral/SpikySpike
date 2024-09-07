// Fill out your copyright notice in the Description page of Project Settings.


#include "SpikySpike/UI/MainMenu.h"

#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Kismet/KismetSystemLibrary.h"
#include "SpikySpike/Player/SSPlayerController.h"

void UMainMenu::NativeConstruct()
{
	Super::NativeConstruct();

	Controller = Cast<ASSPlayerController>(GetWorld()->GetFirstPlayerController());

	WidgetSwitcher_MainMenu->SetActiveWidgetIndex(0);

	Btn_GameStart->OnPressed.AddDynamic(this, &UMainMenu::StartGame);
	Btn_QuitGame->OnPressed.AddDynamic(this, &UMainMenu::QuitGame);
	Btn_QuitYes->OnPressed.AddDynamic(this, &UMainMenu::QuitYes);
	Btn_QuitNo->OnPressed.AddDynamic(this, &UMainMenu::QuitNo);

	PlayAnimation(MainMenuAppearAnimation);
}

void UMainMenu::StartGame()
{
	if(IsValid(Controller))
	{		
		this->RemoveFromParent();

		Controller->ScoreBoardOnViewport();
	}	
}

void UMainMenu::QuitGame()
{
	// Switch To Ask Quit Game
	WidgetSwitcher_MainMenu->SetActiveWidgetIndex(1);
}

void UMainMenu::QuitYes() 
{
	if(IsValid(Controller))
	{
		const TEnumAsByte<EQuitPreference::Type> Types = EQuitPreference::Quit;
		UKismetSystemLibrary::QuitGame(GetWorld(), Controller, Types, false);
	}	
}

void UMainMenu::QuitNo() 
{
	if(IsValid(Controller))
	{
		WidgetSwitcher_MainMenu->SetActiveWidgetIndex(0);
	}	
}
