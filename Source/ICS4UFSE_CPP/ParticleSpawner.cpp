// Copyright (c) 2020 David Hui and Kevin Zhang. ALL RIGHTS RESERVED.


#include "ParticleSpawner.h"

// Sets default values
AParticleSpawner::AParticleSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AParticleSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	// If this system is not perpetual, register a destruction timer
	if (ttl > 0.1) {
		FTimerHandle destroyHandle;
		GetWorldTimerManager().SetTimer(destroyHandle, this, &AParticleSpawner::DestroyParticle, ttl);
	}
	
}

// Called every frame
void AParticleSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Set particle location to location of actor that it is following
	if (FollowActor) {
		SetActorLocation(FollowActor->GetActorLocation());
		SetActorRotation(FollowActor->GetActorRotation());
	}

}

// Destroys the particle system
void AParticleSpawner::DestroyParticle()
{
	Destroy();
}

// Set the actor that this particle system should follow
void AParticleSpawner::SetFollow(AActor* otherActor) {
	FollowActor = otherActor;
}