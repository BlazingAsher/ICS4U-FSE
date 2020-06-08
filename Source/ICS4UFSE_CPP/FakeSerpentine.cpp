// Copyright (c) 2020 David Hui and Kevin Zhang. ALL RIGHTS RESERVED.


#include "FakeSerpentine.h"

void AFakeSerpentine::BeginPlay()
{
	Super::BeginPlay();

	// Destruction handler
	FTimerHandle destroyHandle;

	// Register the self-destruction timer
	GetWorldTimerManager().SetTimer(destroyHandle, this, &AFakeSerpentine::DefaultDestroy, lifespan);
}

// Applies damage
void AFakeSerpentine::ApplyDamage(float Dmg, DmgType Type, AActor* src)
{
	// Intentionally left empty to remove this feature from the ghost
}

// Attacks the player
void AFakeSerpentine::Attack(AActor* actor)
{
	// Intentionally left empty to remove this feature from the ghost
}

// Attacks the player
void AFakeSerpentine::HAttack(AICS4UFSE_CPPCharacter& player)
{
	// Intentionally left empty to remove this feature from the ghost
}

// Attacks the player
void AFakeSerpentine::VAttack(AICS4UFSE_CPPCharacter& player)
{
	// Intentionally left empty to remove this feature from the ghost
}

// Attacks the player
void AFakeSerpentine::FAttack(AICS4UFSE_CPPCharacter& player)
{
	// Intentionally left empty to remove this feature from the ghost
}

// Attacks the player
void AFakeSerpentine::CAttack(AICS4UFSE_CPPCharacter& player)
{
	// Intentionally left empty to remove this feature from the ghost
}

void AFakeSerpentine::DefaultDestroy() {
	Destroy();
}