// Copyright (c) 2020 David Hui and Kevin Zhang. ALL RIGHTS RESERVED.

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

	void BeginPlay();

public:
	void DefaultDestroy();

	UPROPERTY(EditDefaultsOnly)
		float lifespan = 10.f;
};
