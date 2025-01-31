// Copyright (c) 2020 David Hui and Kevin Zhang. ALL RIGHTS RESERVED.


#include "Enemy.h"
#include "Components/CapsuleComponent.h"
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
	armour = FArmour();
	
	BaseCollisionComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("BaseCapsuleComponent"));
	RootComponent = BaseCollisionComponent;
	// create the skeleton
	MySkeleton = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MySkeleton"));
	MySkeleton->SetCollisionProfileName("Pawn");
	MySkeleton->SetupAttachment(RootComponent);
	MySkeleton->SetEnableGravity(true);

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

	// decrease attack cooldown
	if (AtkCldn > 0)
		--AtkCldn;

	if (hp == 0)
		Destroy();

}

// Destroys the enemy
void AEnemy::Destroy(bool x, bool y)
{
	// adds exp to player if it is a player
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

// Attacks the player
void AEnemy::Attack(AActor* actor)
{
	// checks if the cooldown is zero
	if (AtkCldn == 0)
	{
		// cast the reference, apply the damage, and reset the cooldown
		AICS4UFSE_CPPCharacter& player = dynamic_cast<AICS4UFSE_CPPCharacter&>(*actor);
		player.ApplyDamage(MaxDmg, DmgType::DmgMelee, this);
		AtkCldn = MaxAtkCldn;
	}
}

void AEnemy::Walk(bool running)
{
	// walks in the direction it is facing at a speed relative to its maximum speed
	FVector Facing = GetActorRotation().Vector();
	Facing *= running ? ms : ms / 3;
	SetActorLocationAndRotation(GetActorLocation() + Facing, GetActorRotation());
}

// Setters and getters
void AEnemy::SetMaxDmg(float f)
{
	MaxDmg = f;
}

float AEnemy::GetMaxDmg()
{
	return MaxDmg;
}