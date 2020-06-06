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
	FTimerHandle spawnHandle;
	GetWorldTimerManager().SetTimer(spawnHandle, this, &AParticleSpawner::SpawnParticle, SpawnDelay);
	if (ttl < 0.1) {
		FTimerHandle destroyHandle;
		GetWorldTimerManager().SetTimer(destroyHandle, this, &AParticleSpawner::DestroyParticle, ttl);
	}
	
}

// Called every frame
void AParticleSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AParticleSpawner::SpawnParticle()
{
	FActorSpawnParameters SpawnParams;
	SpawnedActor = GetWorld()->SpawnActor<AParticleWrapper>(ParticleWrapperBP, GetTransform(), SpawnParams);
}

void AParticleSpawner::DestroyParticle()
{
	SpawnedActor->Destroy();
}