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

// Attacks the player
void AFakeSerpentine::HAttack(AICS4UFSE_CPPCharacter& player)
{

}

// Attacks the player
void AFakeSerpentine::VAttack(AICS4UFSE_CPPCharacter& player)
{

}

// Attacks the player
void AFakeSerpentine::FAttack(AICS4UFSE_CPPCharacter& player)
{

}

// Attacks the player
void AFakeSerpentine::CAttack(AICS4UFSE_CPPCharacter& player)
{

}

void AFakeSerpentine::DefaultDestroy() {
	Destroy();
}