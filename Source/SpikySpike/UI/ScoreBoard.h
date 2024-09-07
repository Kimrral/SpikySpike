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
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	void SetCountdownTimer();

	// Timer Value Text Block
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTextBlock* CountdownValue;

	// First Team Score Text Block
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTextBlock* FirstTeamScore;

	// Second Team Score Text Block
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTextBlock* SecondTeamScore;

	// Appear Animation
	UPROPERTY(BlueprintReadWrite, Transient, meta = (BindWidgetAnim))
	class UWidgetAnimation* CountdownConstruct;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Countdown = 60.f;

	
};
