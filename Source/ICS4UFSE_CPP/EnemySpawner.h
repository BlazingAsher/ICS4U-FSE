// Copyright (c) 2020 David Hui and Kevin Zhang. ALL RIGHTS RESERVED.
// Generic Actor spawning class that allows control over radius, spawn rate, and spawn amount

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Engine/Engine.h"
#include "EnemySpawner.generated.h"

UCLASS()
class ICS4UFSE_CPP_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Spawn timer handle
	FTimerHandle spawnerHandle;

public:	
	// Mesh and collision component
	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent* MyMesh;

	UPROPERTY()
		class USphereComponent* SphereComponent;

	// The type of actor to spawn
	UPROPERTY(EditAnywhere, Category = "WorldBehaviour")
		TSubclassOf<AActor> ToSpawn;

	// Spawn tick frequency
	UPROPERTY(EditAnywhere, Category = "WorldBehaviour")
		float SpawnTickRate = 1.f;

	// Spawn radius
	UPROPERTY(EditAnywhere, Category = "WorldBehaviour")
		int SpawnRadius = 1000;

	// Maximum amount to spawn per tick
	UPROPERTY(EditAnywhere, Category = "WorldBehaviour")
		int MaxSpawnNum = 1;

	// Minimum amount to spawn per tick
	UPROPERTY(EditAnywhere, Category = "WorldBehaviour")
		int MinSpawnNum = 1;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Trigger a spawn tick
	UFUNCTION()
		void Spawn();
};
