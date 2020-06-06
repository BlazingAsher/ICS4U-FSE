// Copyright (c) 2020 David Hui and Kevin Zhang. ALL RIGHTS RESERVED.


#include "FakeSerpentine.h"

void AFakeSerpentine::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle destroyHandle;

	GetWorldTimerManager().SetTimer(destroyHandle, this, &AFakeSerpentine::DefaultDestroy, lifespan);
}

// Applies damage
void AFakeSerpentine::ApplyDamage(float Dmg, DmgType Type, AActor* src)
{

}

// Attacks the player
void AFakeSerpentine::Attack(AActor* actor)
{

}

void AFakeSerpentine::DefaultDestroy() {
	Destroy();
}