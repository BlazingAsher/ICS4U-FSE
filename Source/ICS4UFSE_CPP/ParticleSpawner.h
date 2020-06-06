// Copyright (c) 2020 David Hui and Kevin Zhang. ALL RIGHTS RESERVED.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ICS4UFSE_CPP/ParticleWrapper.h"
#include "ParticleSpawner.generated.h"

UCLASS()
class ICS4UFSE_CPP_API AParticleSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AParticleSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	AActor* SpawnedActor;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, Category = "SpawningOptions")
		TSubclassOf<AParticleWrapper> ParticleWrapperBP;

	UPROPERTY(EditDefaultsOnly, Category = "SpawningOptions")
		float ttl = 0;

	UPROPERTY(EditDefaultsOnly, Category = "SpawningOptions")
		float SpawnDelay = 0;

	UFUNCTION()
		void SpawnParticle();

	UFUNCTION()
		void DestroyParticle();
};
