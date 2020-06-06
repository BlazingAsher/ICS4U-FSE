// Fill out your copyright notice in the Description page of Project Settings.

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

	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent* MyMesh;

	UPROPERTY()
		class USphereComponent* MySphereComponent;

	UPROPERTY(EditDefaultsOnly, Category = "WorldBehaviour")
		float Lifespan = 15.f;

	UPROPERTY(EditDefaultsOnly, Category = "WorldBehaviour")
		float DamageAmt = 20.f;

	UPROPERTY(EditDefaultsOnly, Category = "WorldBehaviour")
		float DamageTickTime = .5f;

	UFUNCTION()
		virtual void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void DefaultDestroy();

	void DamageTick();

	UFUNCTION()
		void SetDamage(float damage);

	virtual void Destroy(bool bNetForce = false, bool bShouldModifyLevel = true);
	
};
