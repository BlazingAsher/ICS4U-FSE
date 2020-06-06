// Copyright (c) 2020 David Hui and Kevin Zhang. ALL RIGHTS RESERVED.
// Item that player picks up to slowly build the portal to the boss

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PortalComponent.generated.h"

UCLASS()
class ICS4UFSE_CPP_API APortalComponent : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APortalComponent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Mesh and box component
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* MyMesh;

	UPROPERTY()
	class UBoxComponent* MyBoxComponent;

	// Called whenever an actor overlaps with the Portal Component
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
