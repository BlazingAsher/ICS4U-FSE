// Copyright (c) 2020 David Hui and Kevin Zhang. ALL RIGHTS RESERVED.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "ICS4UFSE_CPPCharacter.h"
#include "GameFramework/Actor.h"
#include <ICS4UFSE_CPP\SerpentineType.h>
#include <ICS4UFSE_CPP\ParticleSpawner.h>
#include "Serpentine.generated.h"

UCLASS()
class ICS4UFSE_CPP_API ASerpentine : public AEnemy
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASerpentine();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Warns other enemies of player
	virtual void Warn();

	// Be warned of player presence
	virtual void BeWarned(const FVector& PlayerPos);

	// Functions for different types of serpentine
	void CAttack(AICS4UFSE_CPPCharacter& player);
	void FAttack(AICS4UFSE_CPPCharacter& player);
	void HAttack(AICS4UFSE_CPPCharacter& player);
	void VAttack(AICS4UFSE_CPPCharacter& player);

protected:
	// Warning variables for player prescence
	bool WarnInited;
	unsigned int WarnTimer;

	SerpentineType SType;

	// spawner for illusion effects
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor>FakeSpawner;

	bool AlreadySpawned; // Whether a Venomai fake spawner has already been created

	// Particle effects
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AParticleSpawner> CEffect;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AParticleSpawner> FEffect;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AParticleSpawner> HEffect;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AParticleSpawner> VEffect;

};
