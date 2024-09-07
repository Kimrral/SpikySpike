// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StageResult.generated.h"

/**
 * 
 */
UCLASS()
class SPIKYSPIKE_API UStageResult : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void FirstTeamWin() ;

	UFUNCTION()
	void SecondTeamWin() ;

	UFUNCTION()
	void ReturnToLobby();

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UButton* Btn_ReturnLobby;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UWidgetSwitcher* WidgetSwitcher_StageResult;
	
};
