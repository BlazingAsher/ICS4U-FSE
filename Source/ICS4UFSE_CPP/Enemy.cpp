// Copyright (c) 2020 David Hui and Kevin Zhang. ALL RIGHTS RESERVED.


#include "Enemy.h"
#include <algorithm>
#include <cstdlib>

// Sets default values
AEnemy::AEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Applies damage
void AEnemy::ApplyDamage(float Dmg, DmgType Type)
{
	if (Type < DmgType::DmgFall)
	{
		// apply armour damage
		hp = armour - Dmg;
		if (hp < 0)
			hp = 0;
	}
	else
		hp = std::max(0.0f, hp - Dmg);
}
