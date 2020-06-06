// Copyright (c) 2020 David Hui and Kevin Zhang. ALL RIGHTS RESERVED.


#include "Boss.h"
#include <Runtime\Engine\Classes\Engine\Engine.h>
#include <ICS4UFSE_CPP\ICS4UFSE_CPPCharacter.h>

// Sets default values
ABoss::ABoss()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABoss::BeginPlay()
{
	Super::BeginPlay();

	mxhp = 3000;
	MaxDmg = 0;
	MinDmg = 0;
	ms = 3;

}

// Called every frame
void ABoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AICS4UFSE_CPPCharacter& player = dynamic_cast<AICS4UFSE_CPPCharacter&>(*GetWorld()->GetFirstPlayerController()->GetPawn());
	FVector PosDiff = player.GetActorLocation() - GetActorLocation();
	FRotator RotDiff = PosDiff.ToOrientationRotator() - GetActorRotation();
	FVector FVRotDiff = FVector(RotDiff.Roll, RotDiff.Pitch, RotDiff.Yaw);
	FVRotDiff /= FVRotDiff.Size() * 2;
	RotDiff = FRotator(FVRotDiff.Y, FVRotDiff.Z, FVRotDiff.X);

	SetActorRotation(GetActorRotation() + RotDiff);

	if (PosDiff.Size() < 1000)
	{
		Walk();
	}
	else
		SetActorLocation(GetActorLocation());

}