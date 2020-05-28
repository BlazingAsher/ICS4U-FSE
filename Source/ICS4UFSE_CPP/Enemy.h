// Copyright (c) 2020 David Hui and Kevin Zhang. ALL RIGHTS RESERVED.

#pragma once

#include "CoreMinimal.h"
#include<cmath>
#include "Armour.h"
#include "DmgType.h"
#include "GameFramework/Actor.h"
#include "Enemy.generated.h"

UCLASS()
class ICS4UFSE_CPP_API AEnemy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Applies damage
	virtual void ApplyDamage(float Dmg, DmgType Type, AActor* src = nullptr);

	// Destroys the enemy
	virtual void Destroy(bool x = false, bool y = true);

	// Get the last actor that attacked this enemy
	AActor* GetLastAttackedBy();

protected:

	// Health of the enemy
	float hp, mxhp;

	// Armour of the enemy
	Armour armour;

	// Experience reward
	int exp;

	// Maximum movement speed
	float ms;

	// Last attacked by
	AActor* lab;

	// Damage dealt by the enemy
	float MinDmg, MaxDmg;

	// Damage knockback
	float DmgKnockback;

};
