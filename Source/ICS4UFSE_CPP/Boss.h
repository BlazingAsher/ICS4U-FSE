// Copyright (c) 2020 David Hui and Kevin Zhang. ALL RIGHTS RESERVED.
// Additional functionality for the end boss. Mostly modifies Enemy.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "Kismet/GameplayStatics.h"
#include <Sound/SoundCue.h>
#include "Boss.generated.h"

UCLASS()
class ICS4UFSE_CPP_API ABoss : public AEnemy
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoss();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Sound to play on victory
	UPROPERTY(EditAnywhere)
		USoundCue* VictorySound;

};
