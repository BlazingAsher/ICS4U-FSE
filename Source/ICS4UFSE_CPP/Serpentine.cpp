// Copyright (c) 2020 David Hui and Kevin Zhang. ALL RIGHTS RESERVED.


#include "Serpentine.h"

// Sets default values
ASerpentine::ASerpentine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASerpentine::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASerpentine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

