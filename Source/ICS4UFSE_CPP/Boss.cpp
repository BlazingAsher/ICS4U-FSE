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
	hp = mxhp;
	MaxDmg = 3;
	MinDmg = 3;
	ms = 3;
	MaxAtkCldn = 30;

}

// Called every frame
void ABoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AICS4UFSE_CPPCharacter& player = dynamic_cast<AICS4UFSE_CPPCharacter&>(*GetWorld()->GetFirstPlayerController()->GetPawn());
	FVector PosDiff = player.GetActorLocation() - GetActorLocation();
	float Theta = std::acos((PosDiff | GetActorRotation().Vector()) / PosDiff.Size()) * 180 / 3.1415926535897932;
	
	if (Theta < 1)
		SetActorRotation(PosDiff.ToOrientationQuat());
	else
	{
		FRotator RotDiff = PosDiff.ToOrientationRotator() - GetActorRotation();
		FVector FVRotDiff = FVector(RotDiff.Roll, RotDiff.Pitch, RotDiff.Yaw);
		FVRotDiff /= FVRotDiff.Size() * 2;
		RotDiff = FRotator(FVRotDiff.Y, FVRotDiff.Z, FVRotDiff.X);
		SetActorRotation(GetActorRotation() + RotDiff);
	}

	if (PosDiff.Size() > 200 && PosDiff.Size() < 3000)
	{
		Walk();
	}
	else
		SetActorLocation(GetActorLocation());

	if (Theta < 45 && PosDiff.Size() < 300)
	{
		Attack(&player);
		
		if (AtkCldn == MaxAtkCldn)
		{
			FVector launch = GetActorRotation().Vector() + FVector{ 0.0f, 0.0f, 2.0f };
			launch *= 1000;
			// launch the player
			player.LaunchPlayer(launch);
		}
	}

}