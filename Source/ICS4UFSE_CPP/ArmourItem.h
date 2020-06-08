// Copyright (c) 2020 David Hui and Kevin Zhang. ALL RIGHTS RESERVED.
// Item that players can pick up to restore armour status

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ArmourItem.generated.h"

UCLASS()
class ICS4UFSE_CPP_API AArmourItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AArmourItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	
	UPROPERTY(EditAnywhere)
	// Hardness increment
	float HardImpr = 5;

	UPROPERTY(EditAnywhere)
	// Toughness increment
	float ToughImpr = 5;

	// Item mesh and collision components
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* MyMesh;

	UPROPERTY()
	class UBoxComponent* MyBoxComponent;

};
