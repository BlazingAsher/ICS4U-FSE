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

	// Attacks the player
	virtual void Attack(AActor* actor);

	// Get the last actor that attacked this enemy
	AActor* GetLastAttackedBy();

	// Walk the enemy
	virtual void Walk(bool running = false);

protected:
	UPROPERTY(EditAnywhere)
	// Health of the enemy
	float mxhp = 10, hp = 10;

	// Armour of the enemy
	FArmour armour;

	UPROPERTY(EditAnywhere)
	// Experience reward
	int exp = 5;

	UPROPERTY(EditAnywhere)
	// Maximum attack cooldown
	int MaxAtkCldn = 60;

	// Attack cooldown
	int AtkCldn;

	UPROPERTY(EditAnywhere)
	// Maximum movement speed
	float ms = 2;

	// Last attacked by
	AActor* lab;

	UPROPERTY(EditAnywhere)
	// Damage dealt by the enemy
	float MinDmg = 0.125;
	
	UPROPERTY(EditAnywhere)
	// Maximum damage
	float MaxDmg = 0.25;

	UPROPERTY(EditAnywhere)
	// Damage knockback
	float DmgKnockback;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* MyMesh;

	UPROPERTY()
	class UBoxComponent* MyBoxComponent;

};
