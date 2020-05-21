// Copyright (c) 2020 David Hui and Kevin Zhang. ALL RIGHTS RESERVED.

#pragma once

#include "CoreMinimal.h"
#include<cmath>
#include "DmgType.h"
#include "Armour.h"
#include "GameFramework/Actor.h"
#include "Skulkin.generated.h"

UCLASS()
class ICS4UFSE_CPP_API ASkulkin : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASkulkin();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Applies damage
	virtual void ApplyDamage(float Dmg, DmgType Type);

	// Warns other enemies of player
	virtual void Warn();

protected:
	// Health of the Skulkin
	float hp, mxhp;
	// Armour of the Skulkin
	Armour SkulkinArmour;
	// Warning variables for player prescence
	bool WarnInited;
	unsigned int WarnTimer;

};
