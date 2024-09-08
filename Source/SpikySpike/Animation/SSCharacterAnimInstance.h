// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "SpikySpike/Ball/SSVolleyBall.h"
#include "NiagaraFunctionLibrary.h"
#include "SSCharacterAnimInstance.generated.h"


/**
 * 
 */
UCLASS()
class SPIKYSPIKE_API USSCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
protected:
	virtual void NativeBeginPlay() override;
	
public:
	UFUNCTION()
	void AnimNotify_SpikeHitPoint();

	UPROPERTY(VisibleAnywhere)
	class ASSCharacter* AnimOwner;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BallDetectRange = 200.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpikeForce = 5000.f;

	void SpikeBall(const ASSVolleyBall* VolleyBall) const;
	void SpikeBall2(const ASSVolleyBall* VolleyBall) const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UNiagaraSystem* SpikeParticle;
	
protected:
	bool IsPlayerFacingRight() const;
};
