// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class SPIKYSPIKE_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;
	
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UButton* Btn_GameStart;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UButton* Btn_QuitGame;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UWidgetSwitcher* WidgetSwitcher_MainMenu;

	UPROPERTY()
	class APlayerController* Controller;

	UFUNCTION()
	void StartGame();

	UFUNCTION()
	void QuitGame();

	UFUNCTION()
	void QuitYes() const;

	UFUNCTION()
	void QuitNo() const;
	
};
