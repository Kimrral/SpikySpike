// Fill out your copyright notice in the Description page of Project Settings.


#include "SpikySpike/Animation/SSCharacterAnimInstance.h"

#include "Kismet/GameplayStatics.h"
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
		DrawDebugSphere(GetWorld(), Center, BallDetectRange, 70, FColor::Red, false, 3.0f);
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
				//SpikeBall(VolleyBall);
				SpikeBall2(VolleyBall);
				UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), SpikeParticle,
				                                               AnimOwner->GetMesh()->GetBoneLocation(
					                                               FName("SpikeParticleSocket")));
			}
		}
	}
}

void USSCharacterAnimInstance::SpikeBall(const ASSVolleyBall* VolleyBall) const
{
	// 대각선 아래 방향으로 힘을 가합니다 (45도 각도)
	const FVector DiagonalForceDirection = FVector(1.0f, 1.0f, -1.0f).GetSafeNormal();
	const FVector Force = DiagonalForceDirection * SpikeForce;

	VolleyBall->BallMesh->AddForce(FVector(100000));
}

// 플레이어의 방향을 고려한 스파이크 함수
void USSCharacterAnimInstance::SpikeBall2(const ASSVolleyBall* VolleyBall) const
{
	// 플레이어가 왼쪽/오른쪽을 보고 있는지에 따라 스파이크 방향이 결정
	const FVector DiagonalForceDirection = (IsPlayerFacingRight()
		                                        ? FVector(0.f, 1.0f, -1.0f)
		                                        : FVector(0.f, -1.0f, -1.0f)).GetSafeNormal();

	// 일단은 SpiekForce 대신 하드 코딩 상수를 사용
	VolleyBall->BallMesh->AddForce(DiagonalForceDirection * 100'0000.F);
	DrawDebugDirectionalArrow(GetWorld(), AnimOwner->GetActorLocation(),
	                          AnimOwner->GetActorLocation() + DiagonalForceDirection * 100, 2, FColor::Green, false,
	                          3.0f, 0, 2.f);

	UGameplayStatics::PlaySound2D(GetWorld(), SpikeSound);
}

// 내적을 활용해 플레이어가 왼쪽/오른쪽을 보고 있는지 반환
bool USSCharacterAnimInstance::IsPlayerFacingRight() const
{
	if (!IsValid(AnimOwner))
	{
		return false;
	}

	const FVector CharacterForwardVector = FVector::VectorPlaneProject(AnimOwner->GetActorForwardVector(),
	                                                                   FVector::UpVector);
	const float Dot = FVector::DotProduct(CharacterForwardVector, FVector::RightVector);

	return (0.f < Dot);
}
