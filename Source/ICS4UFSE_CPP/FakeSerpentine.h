// Copyright (c) 2020 David Hui and Kevin Zhang. ALL RIGHTS RESERVED.
// Actor that is spawned in by Venomai actor. Acts like a ghost. Cannot attack or be attacked.

#pragma once

#include "CoreMinimal.h"
#include "Serpentine.h"
#include "FakeSerpentine.generated.h"

/**
 * 
 */
UCLASS()
class ICS4UFSE_CPP_API AFakeSerpentine : public ASerpentine
{
	GENERATED_BODY()
	
	// Override so that it cannot have damage applied to it
	virtual void ApplyDamage(float Dmg, DmgType Type, AActor* src = nullptr);

	// Override so that it cannot attack
	virtual void Attack(AActor* actor);

	// Override so that it cannot attack
	virtual void CAttack(AICS4UFSE_CPPCharacter& player);

	// Override so that it cannot attack
	virtual void VAttack(AICS4UFSE_CPPCharacter& player);

	// Override so that it cannot attack
	virtual void HAttack(AICS4UFSE_CPPCharacter& player);

	// Override so that it cannot attack
	virtual void FAttack(AICS4UFSE_CPPCharacter& player);

	void BeginPlay();

public:
	// Destroy wrapper without parameters
	void DefaultDestroy();

	// How long this ghost should live
	UPROPERTY(EditDefaultsOnly)
		float lifespan = 10.f;
};
