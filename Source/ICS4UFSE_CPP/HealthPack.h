// Copyright (c) 2020 David Hui and Kevin Zhang. ALL RIGHTS RESERVED.
// Item that can be picked up to restore health to the player

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HealthPack.generated.h"

UCLASS()
class ICS4UFSE_CPP_API AHealthPack : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHealthPack();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:

	// Amount of health to recover
	UPROPERTY(EditAnywhere)
	float RecoveryPower = 1;

};
