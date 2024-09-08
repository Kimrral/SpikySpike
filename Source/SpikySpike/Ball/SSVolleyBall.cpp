// Fill out your copyright notice in the Description page of Project Settings.

#include "SSVolleyBall.h"
#include "SpikySpike/GameMode/SSGameState.h"
#include "Kismet/GameplayStatics.h"

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

    bReplicates = true;
    SetReplicatingMovement(true);
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
    HandleBallCollision(OtherActor);
}

void ASSVolleyBall::HandleBallCollision(AActor* OtherActor) const
{
    if (HasAuthority() && OtherActor)
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
	else if (OtherActor)
	{
		if (OtherActor->ActorHasTag("Floor") || OtherActor->ActorHasTag("Wall"))
		{
			UGameplayStatics::PlaySound2D(GetWorld(), BounceSound);
		}
	}
}

