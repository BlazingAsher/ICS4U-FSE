// Copyright (c) 2020 David Hui and Kevin Zhang. ALL RIGHTS RESERVED.

#include "Skulkin.h"
#include "Engine/World.h"
#include <algorithm>
#include <cstdlib>

template<typename B,typename D>
bool is_base_of(const B& b, const D& d)
{
	return std::is_base_of<B, D>::value;
}

// constance that will be used
float ASkulkin::FOV = 60;
float ASkulkin::WarnDist = 100;
float ASkulkin::ViewDist = 100;

// Sets default values
ASkulkin::ASkulkin()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Sets the max health and current health
	mxhp = 10;
	hp = mxhp;

}

// Called when the game starts or when spawned
void ASkulkin::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASkulkin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector PlayerPos = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation(), ThisPos = GetActorLocation();
	FVector PosDiff = PlayerPos - ThisPos;
	float magnitude = PosDiff.Size();

	FVector Facing = GetActorRotation().Vector();
	float Theta = std::acos(Facing | PosDiff / magnitude);
	
	// The enemy will detect player if it is within field of view.
	// Make sure to implement pigman like warning
	if (magnitude < 100 && Theta < 60)
	{

		// face the player
		SetActorRotation(PosDiff.ToOrientationRotator());
		HasTarget = true;

		// warn the others
		Warn();

	}
	else
	{
		// a random number deciding to randomly turn
		unsigned int RndNum = std::rand() % 3600;

		if (RndNum == 0)
		{
			float pitch = RndNum / 10, yaw = std::rand() % 360;
			SetActorRotation({ pitch, yaw, 0.0f });
		}
	}

	if (WarnInited && WarnTimer == 0)
	{
		// Get all of the actors and warn them if they are also a Skulkin
		GetWorld();
		WarnInited = false;

		AActor* begin, * end;
		ASkulkin* sk;

		for (; begin != end; ++begin)
		{
			if ((begin->GetActorLocation() - ThisPos).Size()<is_base_of(ASkulkin(), *begin))
			{
				// cast the pointer
				sk = (ASkulkin*)begin;

				// only warn if it doesn't have a target yet
				if (!sk->HasTarget)
					sk->BeWarned(PlayerPos - sk->GetActorLocation());
				
			}
		}

	}

	// Decrease the warning timer
	if (WarnInited && WarnTimer > 0)
		--WarnTimer;

	// Slow regeneration
	if (hp < mxhp)
		hp += 0.01;
	if (hp > mxhp)
		hp = mxhp;

	if (magnitude > 2)
		ThisPos += Facing / 12;

	// Setting the actor location will cause the rotation to update
	// Setting the actor rotation will do nothing if location is not set
	SetActorLocation(ThisPos);

}

// Applies damage
void ASkulkin::ApplyDamage(float Dmg, DmgType Type)
{
	if (Type < DmgType::DmgFall)
	{
		// apply armour damage
		hp = SkulkinArmour - Dmg;
		if (hp < 0)
			hp = 0;
	}
	else
		hp = std::max(0.0f, hp - Dmg);
}

// Warns other enemies of player
void ASkulkin::Warn()
{
	WarnTimer = 300;
	WarnInited = true;
}

void ASkulkin::BeWarned(const FVector& PlayerPos)
{
	// face the player
	SetActorRotation(PlayerPos.ToOrientationRotator());
	// now has a target
	HasTarget = true;
}

// Getters and setters
float ASkulkin::HP()
{
	return hp;
}

void ASkulkin::HP(float hp)
{
	this->hp = hp;
}

float ASkulkin::MaxHP()
{
	return mxhp;
}

void ASkulkin::MaxHP(float hp)
{
	this->mxhp = mxhp;
}

Armour ASkulkin::SArmour()
{
	return SkulkinArmour;
}

void ASkulkin::SArmour(Armour SkulkinArmour)
{
	this->SkulkinArmour = SkulkinArmour;
}

bool ASkulkin::WarnInit()
{
	return WarnInited;
}

void ASkulkin::WarnInit(bool b)
{
	WarnInited = b;
}

unsigned int ASkulkin::WarnTmr()
{
	return WarnTimer;
}

void ASkulkin::WarnTmr(unsigned int tmr)
{
	WarnTimer = tmr;
}

bool ASkulkin::WarnInit()
{
	return WarnInited;
}

void ASkulkin::WarnInit(bool b)
{
	HasTarget = b;
}