// Copyright (c) 2020 David Hui and Kevin Zhang. ALL RIGHTS RESERVED.

#include "Skulkin.h"
#include "Engine/World.h"
#include <algorithm>
#include <cstdlib>

// Sets default values
ASkulkin::ASkulkin()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Sets the max health and current health
	mxhp = 10;
	hp = mxhp;

}

// Called when the game starts or when spawned
void ASkulkin::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASkulkin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector PlayerPos = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation(), ThisPos = GetActorLocation();
	FVector PosDiff = PlayerPos - ThisPos;
	float magnitude = PosDiff.Size();

	FVector Facing = GetActorRotation().Vector();
	float Theta = std::acos(Facing | PosDiff / magnitude);
	
	// The enemy will detect player if it is within field of view.
	// Make sure to implement pigman like warning
	if (Theta < 60)
		SetActorRotation(PosDiff.ToOrientationRotator());
	else
	{
		// a random number deciding to randomly turn
		unsigned int RndNum = std::rand() % 3600;

		if (RndNum == 0)
		{
			float pitch = RndNum / 10, yaw = std::rand() % 360;
			SetActorRotation({ pitch, yaw, 0.0f });
		}
	}

	//FVector MovementVector = ThisRotation.RotateVector({ 1,0,0 });
	//SetActorLocation(ThisPos - MovementVector * 0.25);

	// Setting the actor location will cause the rotation to update
	// Setting the actor rotation will do nothing if location is not set
	SetActorLocation(ThisPos);

}

// Warns other enemies of player
void ASkulkin::Warn()
{
	WarnTimer = 300;
	WarnInited = true;
}