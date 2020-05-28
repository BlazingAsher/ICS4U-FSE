// Copyright (c) 2020 David Hui and Kevin Zhang. ALL RIGHTS RESERVED.


#include "Enemy.h"
#include <algorithm>
#include <cstdlib>
#include <ICS4UFSE_CPP\ICS4UFSE_CPPCharacter.h>
#include <Runtime\Engine\Classes\Engine\Engine.h>

// Sets default values
AEnemy::AEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// By default, the armour is zero
	armour = Armour();

	// Default damage values
	MinDmg = 0.125;
	MaxDmg = 0.25;
	DmgKnockback = 10;

	// this is temporary, and should be in subclasses
	mxhp = 10;
	hp = mxhp;
	exp = 10;

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

	if (hp == 0)
		Destroy();

}

// Destroys the enemy
void AEnemy::Destroy(bool x, bool y)
{
	if (dynamic_cast<AICS4UFSE_CPPCharacter*>(lab))
		((AICS4UFSE_CPPCharacter*)lab)->AddExp(exp);
	Super::Destroy(x, y);
}

// Applies damage
void AEnemy::ApplyDamage(float Dmg, DmgType Type, AActor* src)
{
	if (src)
		lab = src;
	if (Type < DmgType::DmgFall)
	{
		// apply armour damage
		hp -= armour - Dmg;
		if (hp < 0)
			hp = 0;
	}
	else
		hp = std::max(0.0f, hp - Dmg);
}
