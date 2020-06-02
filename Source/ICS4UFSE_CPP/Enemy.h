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
	UPROPERTY(EditAnywhere)
	// Health of the enemy
	float hp = 10, mxhp = 10;

	// Armour of the enemy
	Armour armour;

	UPROPERTY(EditAnywhere)
	// Experience reward
	int exp = 5;

	UPROPERTY(EditAnywhere)
	// Maximum movement speed
	float ms = 10;

	// Last attacked by
	AActor* lab;

	UPROPERTY(EditAnywhere)
	// Damage dealt by the enemy
	float MinDmg = 0.125, MaxDmg = 0.25;

	UPROPERTY(EditAnywhere)
	// Damage knockback
	float DmgKnockback;

};
