// Copyright (c) 2020 David Hui and Kevin Zhang. ALL RIGHTS RESERVED.

#include "Skulkin.h"
#include "Engine/World.h"

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

	FRotator ThisRotation = { std::fmod(std::atan2(PosDiff.X, PosDiff.Z) * 180.0f / 3.1415926535897932f + 360.0f, 360.0f), std::fmod(std::atan2(PosDiff.Y, PosDiff.X) * 180.0f / 3.1415926535897932f + 360.0f, 360.0f), 0.0f };
	SetActorRotation(ThisRotation);

	FVector MovementVector = ThisRotation.RotateVector({ 1,0,0 });
	SetActorLocation(ThisPos - MovementVector * 0.25);

}

