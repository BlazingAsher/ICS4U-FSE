// Copyright (c) 2020 David Hui and Kevin Zhang. ALL RIGHTS RESERVED.

#define FinishAnimation()do{DegsAnimated=0;IsAnimating=0;}while(0)
#include "Door.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set default animating and open state
	IsAnimating = 0;
	IsOpen = 0;

	// Set default degrees animated
	DegsAnimated = 0;

}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsAnimating)
	{
		// test if animation should be finished
		if (DegsAnimated < 90)
		{
			// gets the location and rotation
			FRotator ThisRot = GetActorRotation();
			FVector ThisPos = GetActorLocation();
			FRotator PivDiff = (ThisPos - Pivot).ToOrientationRotator();

			if (YawPos == IsOpen)
				ThisRot.Yaw += 3;
			else
				ThisRot.Yaw -= 3;
			if (YawPos == IsOpen)
				PivDiff.Yaw += 3;
			else
				PivDiff.Yaw -= 3;
			ThisPos = Pivot + PivDiff.Vector() * (ThisPos - Pivot).Size();

			SetActorRotation(ThisRot);
			SetActorLocation(ThisPos);
			DegsAnimated += 3;
		}
		else
			FinishAnimation();
	}

}

void ADoor::ToggleDoor()
{
	if (!IsAnimating)
	{

		// sets the state of the door
		IsOpen = !IsOpen;
		IsAnimating = true;

	}
}

// Getters and setters
bool ADoor::Opened()
{
	return IsOpen;
}

void ADoor::Opened(bool b)
{
	IsOpen = b;
}

bool ADoor::Animating()
{
	return IsAnimating;
}

void ADoor::Animating(bool b)
{
	IsAnimating = b;
}

float ADoor::AnimDegrees()
{
	return DegsAnimated;
}

void ADoor::AnimDegrees(float f)
{
	DegsAnimated = f;
}

FVector ADoor::DoorPivot()
{
	return Pivot;
}

void ADoor::DoorPivot(const FVector& piv)
{
	Pivot = piv;
}