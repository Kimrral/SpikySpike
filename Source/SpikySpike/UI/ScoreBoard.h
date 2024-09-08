// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScoreBoard.generated.h"

/**
 * 
 */
UCLASS()
class SPIKYSPIKE_API UScoreBoard : public UUserWidget
{
	GENERATED_BODY()

	
public:
	virtual void NativeConstruct() override;

	// First Team Score Text Block
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTextBlock* FirstTeamScore;

	// Second Team Score Text Block
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UTextBlock* SecondTeamScore;

	UPROPERTY()
	int32 FirstTeamScoreNumber = 0;

	UPROPERTY()
	int32 SecondTeamScoreNumber = 0;

	
};
