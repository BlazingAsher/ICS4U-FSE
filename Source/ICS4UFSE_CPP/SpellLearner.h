// Copyright (c) 2020 David Hui and Kevin Zhang. ALL RIGHTS RESERVED.
// An item that the player picks up to level up their spell casting abilities

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include <ICS4UFSE_CPP/ICS4UFSE_CPPCharacter.h>
#include "SpellLearner.generated.h"

UCLASS()
class ICS4UFSE_CPP_API ASpellLearner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpellLearner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Mesh and Collision Box Components
	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent* MyMesh;

	UPROPERTY()
		class USphereComponent* PortalComponent;

	// Called when another actor overlaps the Spell Learner
	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
