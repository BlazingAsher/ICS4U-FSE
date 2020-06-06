// Copyright (c) 2020 David Hui and Kevin Zhang. ALL RIGHTS RESERVED.
// Wraps a Particle system to allow it to be spawned in C++

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ICS4UFSE_CPP/ParticleWrapper.h"
#include "ParticleSpawner.generated.h"

UCLASS()
class ICS4UFSE_CPP_API AParticleSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AParticleSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Actor that this particle system follows
	AActor* FollowActor;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Lifespan of the particle system
	UPROPERTY(EditDefaultsOnly, Category = "SpawningOptions")
		float ttl = 0;

	// Destroys the system
	UFUNCTION()
		void DestroyParticle();

	// Set an actor for this system to follow
	UFUNCTION()
		void SetFollow(AActor* otherActor);
};
