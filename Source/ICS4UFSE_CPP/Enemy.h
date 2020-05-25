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
	virtual void ApplyDamage(float Dmg, DmgType Type);

protected:

	// Health of the enemy
	float hp, mxhp;

	// Armour of the enemy
	Armour armour;

};
