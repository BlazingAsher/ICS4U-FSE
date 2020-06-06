// Copyright (c) 2020 David Hui and Kevin Zhang. ALL RIGHTS RESERVED.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ParticleWrapper.generated.h"

UCLASS()
class ICS4UFSE_CPP_API AParticleWrapper : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AParticleWrapper();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
