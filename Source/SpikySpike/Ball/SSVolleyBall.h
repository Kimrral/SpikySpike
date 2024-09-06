// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SSVolleyBall.generated.h"

UCLASS()
class SPIKYSPIKE_API ASSVolleyBall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASSVolleyBall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:    
    virtual void Tick(float DeltaTime) override;

    // Handle collision with other actors
    UFUNCTION()
    void OnBallHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

private:
    // The static mesh component for the ball
    UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> BallMesh;

	// Function to handle scoring based on the ball collision
    void HandleBallCollision(AActor* OtherActor);
};