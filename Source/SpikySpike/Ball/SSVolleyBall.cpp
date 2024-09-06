// Fill out your copyright notice in the Description page of Project Settings.

#include "SSVolleyBall.h"
#include "SpikySpike/GameMode/SSGameState.h"

// Sets default values
ASSVolleyBall::ASSVolleyBall()
{
    PrimaryActorTick.bCanEverTick = true;

    // Create and set up the static mesh component
    BallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BallMesh"));
    RootComponent = BallMesh;

    // Enable physics simulation
    BallMesh->SetSimulatePhysics(true);
    BallMesh->SetNotifyRigidBodyCollision(true);

    // Bind the OnBallHit function to the OnComponentHit event
    BallMesh->OnComponentHit.AddDynamic(this, &ASSVolleyBall::OnBallHit);
}

void ASSVolleyBall::BeginPlay()
{
    Super::BeginPlay();

}

void ASSVolleyBall::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

void ASSVolleyBall::OnBallHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	// Calculate reflection vector
	const FVector IncomingVelocity = HitComponent->GetComponentVelocity();
	const FVector Normal = Hit.Normal;
	const FVector Reflection = FMath::GetReflectionVector(IncomingVelocity, Normal);

    // Apply reflection force
    HitComponent->AddImpulse(Reflection, NAME_None, true);

    HandleBallCollision(OtherActor);
}

void ASSVolleyBall::HandleBallCollision(AActor* OtherActor) const
{
    if (!HasAuthority())
    {
	    return;
    }

    if (OtherActor)
    {
        // Check if the hit actor is a floor
        if (OtherActor->ActorHasTag("Floor"))
        {
            // Get the GameMode
            ASSGameState* SSGameState = Cast<ASSGameState>(GetWorld()->GetGameState());
        	if (SSGameState)
            {
                // Call GameMode to handle scoring
                SSGameState->HandleBallTouch(OtherActor);
            }
        }
    }
}

