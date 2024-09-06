// Fill out your copyright notice in the Description page of Project Settings.


#include "SpikySpike/Animation/SSCharacterAnimInstance.h"

#include "SpikySpike/Ball/SSVolleyBall.h"
#include "SpikySpike/Character/SSCharacter.h"

void USSCharacterAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
}

void USSCharacterAnimInstance::AnimNotify_SpikeHitPoint()
{
	AnimOwner = Cast<ASSCharacter>(GetOwningActor());
	if (IsValid(AnimOwner))
	{
		const FVector Center = AnimOwner->GetMesh()->GetComponentLocation();
		TArray<FOverlapResult> HitObj;
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(AnimOwner);
		DrawDebugSphere(GetWorld(), Center, BallDetectRange, 70, FColor::Red);
		if (const bool bHit = GetWorld()->OverlapMultiByChannel(HitObj, Center, FQuat::Identity, ECC_Visibility,
		                                                        FCollisionShape::MakeSphere(BallDetectRange),
		                                                        Params); bHit == false)
		{
			return;
		}
		for (int i = 0; i < HitObj.Num(); ++i)
		{
			if (const ASSVolleyBall* VolleyBall = Cast<ASSVolleyBall>(HitObj[i].GetActor()); IsValid(VolleyBall))
			{
				SpikeBall(VolleyBall);
				UE_LOG(LogTemp, Warning, TEXT("Spike Casting Succeess"))
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Spike Casting false"))
	}
}

void USSCharacterAnimInstance::SpikeBall(const ASSVolleyBall* VolleyBall) const
{
	// 대각선 아래 방향으로 힘을 가합니다 (45도 각도)
	const FVector DiagonalForceDirection = FVector(1.0f, 1.0f, -1.0f).GetSafeNormal();
	const FVector Force = DiagonalForceDirection * SpikeForce;

	VolleyBall->BallMesh->AddForce(FVector(100000));
}
