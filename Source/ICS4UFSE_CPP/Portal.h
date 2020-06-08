// Copyright (c) 2020 David Hui and Kevin Zhang. ALL RIGHTS RESERVED.
// Portal to teleport the player to the boss

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include <ICS4UFSE_CPP/ParticleSpawner.h>
#include <Sound\SoundCue.h>
#include "Portal.generated.h"

UCLASS()
class ICS4UFSE_CPP_API APortal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APortal();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Mesh and collision component
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* MyMesh;

	UPROPERTY()
	class USphereComponent* PortalComponent;

	// Material to display when portal is on
	UPROPERTY(EditAnywhere)
	class UMaterial* OnMaterial;

	// Material to display when portal is off
	UPROPERTY(EditAnywhere)
	class UMaterial* OffMaterial;

	// Portal particle spawner
	UPROPERTY(EditInstanceOnly)
		TSubclassOf<AParticleSpawner> ParticleSpawner;

	// Called when actor overlaps the portal
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// Activate the portal
	UFUNCTION()
		void ActivatePortal();

	// Reference to the sound to play on teleport
	UPROPERTY(EditAnywhere)
		USoundCue* TeleportSound;
};
