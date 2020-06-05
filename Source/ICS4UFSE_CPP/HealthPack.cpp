// Copyright (c) 2020 David Hui and Kevin Zhang. ALL RIGHTS RESERVED.


#include "HealthPack.h"
#include <Runtime\Engine\Classes\Engine\Engine.h>
#include <ICS4UFSE_CPP\ICS4UFSE_CPPCharacter.h>

// Sets default values
AHealthPack::AHealthPack()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHealthPack::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHealthPack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AICS4UFSE_CPPCharacter& player = dynamic_cast<AICS4UFSE_CPPCharacter&>(*GetWorld()->GetFirstPlayerController()->GetPawn());
	if ((player.GetActorLocation() - GetActorLocation()).Size() < 100)
	{
		player.Heal(RecoveryPower);
		Destroy();
	}

}