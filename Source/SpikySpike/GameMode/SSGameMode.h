// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "SSGameMode.generated.h"

class ASSVolleyBall;
class ASSPlayerState;

UCLASS(minimalapi)
class ASSGameMode : public AGameMode
{
	GENERATED_BODY()

public:
    ASSGameMode();

    FORCEINLINE int32 GetGoalScore() const { return GoalScore; }

    void RestartMatch();

    virtual void EndMatch() override;

	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;

    UPROPERTY(EditAnywhere, NoClear, BlueprintReadOnly, Category=Classes)
	TSubclassOf<ASSVolleyBall> VolleyBallClass;

    FTimerHandle RoundTimerHandle;

protected:
    virtual void BeginPlay() override;

    virtual void StartMatch() override;

    virtual void PostLogin(APlayerController* NewPlayer) override;

private:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GameRules", meta = (AllowPrivateAccess = true))
    int32 GoalScore;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GameRules", meta = (AllowPrivateAccess = true))
    float RoundTimeSeconds;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GameRules", meta = (AllowPrivateAccess = true))
    FVector BallSpawnLocation;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GameRules", meta = (AllowPrivateAccess = true))
    TWeakObjectPtr<ASSVolleyBall> SSVolleyBall;
};
