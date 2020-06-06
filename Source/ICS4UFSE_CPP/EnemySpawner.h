// Copyright (c) 2020 David Hui and Kevin Zhang. ALL RIGHTS RESERVED.

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

	FTimerHandle spawnerHandle;

public:	
	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent* MyMesh;

	UPROPERTY()
		class USphereComponent* PortalComponent;

	UPROPERTY(EditAnywhere, Category = "WorldBehaviour")
		TSubclassOf<AActor> ToSpawn;

	UPROPERTY(EditAnywhere, Category = "WorldBehaviour")
		float SpawnTickRate = 1.f;

	UPROPERTY(EditAnywhere, Category = "WorldBehaviour")
		int SpawnRadius = 1000;

	UPROPERTY(EditAnywhere, Category = "WorldBehaviour")
		int MaxSpawnNum = 1;

	UPROPERTY(EditAnywhere, Category = "WorldBehaviour")
		int MinSpawnNum = 1;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void Spawn();
};
