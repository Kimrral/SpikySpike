// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SSPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SPIKYSPIKE_API ASSPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	UFUNCTION()
	void ScoreBoardOnViewport();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UI")
	TSubclassOf<UUserWidget> ScoreBoardWidget;

	UPROPERTY()
	class UScoreBoard* ScoreBoard;
	
	UPROPERTY(EditDefaultsOnly, Category="Camera")
	class UClass* CameraActorClass;

	UFUNCTION(Client, Reliable)
	void SetViewTargetClient();
};
