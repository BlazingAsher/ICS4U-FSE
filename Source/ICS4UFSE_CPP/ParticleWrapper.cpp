// Copyright (c) 2020 David Hui and Kevin Zhang. ALL RIGHTS RESERVED.


#include "ParticleWrapper.h"

// Sets default values
AParticleWrapper::AParticleWrapper()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AParticleWrapper::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AParticleWrapper::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

