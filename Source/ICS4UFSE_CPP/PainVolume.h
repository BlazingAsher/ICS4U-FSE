// Fill out your copyright notice in the Description page of Project Settings.
// Applies damage to all Enemies that are within this sphere

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "PainVolume.generated.h"

UCLASS()
class ICS4UFSE_CPP_API APainVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APainVolume();
	void Attack(class AActor* Target);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere)
	USphereComponent* HitArea;

private:
	UPROPERTY(VisibleAnywhere)
	bool inVolume;

	AActor* SpawnedBy;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Mesh and Collision Box Components
	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent* MyMesh;

	UPROPERTY()
		class USphereComponent* MySphereComponent;

	// Lifespan of the Pain VL
	UPROPERTY(EditDefaultsOnly, Category = "WorldBehaviour")
		float Lifespan = 15.f;

	// Amount of damage done per damage tick
	UPROPERTY(EditDefaultsOnly, Category = "WorldBehaviour")
		float DamageAmt = 20.f;

	// Time between damage ticks
	UPROPERTY(EditDefaultsOnly, Category = "WorldBehaviour")
		float DamageTickTime = .5f;

	// Called when an Actor overlaps with the Pain VL
	UFUNCTION()
		virtual void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// Utility; destroy function without parameters
	void DefaultDestroy();

	// Called every damage tick
	void DamageTick();

	// Set the amount of damage done per damage tick
	UFUNCTION()
		void SetDamage(float damage);
	
};
