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

	// field of view
	static float FOV;

	// distance for warning others of player precense
	static float WarnDist;

	// distance that it can detect a player
	static float ViewDist;

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

	// Be warned of player presence
	virtual void BeWarned(const FVector& PlayerPos);

	// Getters and setters
	float HP();
	void HP(float hp);

	float MaxHP();
	void MaxHP(float mxhp);

	Armour SArmour();
	void SArmour(Armour SkulkinArmour);

	bool WarnInit();
	void WarnInit(bool b);

	unsigned int WarnTmr();
	void WarnTmr(unsigned int tmr);

	bool HasTarg();
	void HasTarg(bool HasTarget);

protected:
	// Health of the Skulkin
	float hp, mxhp;
	// Armour of the Skulkin
	Armour SkulkinArmour;
	// Warning variables for player prescence
	bool WarnInited;
	unsigned int WarnTimer;
	bool HasTarget;

};
