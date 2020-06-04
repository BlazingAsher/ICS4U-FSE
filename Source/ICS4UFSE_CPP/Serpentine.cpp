// Copyright (c) 2020 David Hui and Kevin Zhang. ALL RIGHTS RESERVED.


#include "Serpentine.h"
#include <chrono>
#include "Kismet/GameplayStatics.h"
#include "Templates/SubclassOf.h"
#include "ICS4UFSE_CPPCharacter.h"
#include <Runtime\Engine\Classes\Engine\Engine.h>

// Sets default values
ASerpentine::ASerpentine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASerpentine::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASerpentine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector PlayerPos = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation(), ThisPos = GetActorLocation();
	FVector PosDiff = PlayerPos - ThisPos;
	float magnitude = PosDiff.Size();

	FVector Facing = GetActorRotation().Vector();
	float Theta = std::acos((Facing | PosDiff) / magnitude) * 180 / 3.1415926535897932;

	// decrease attack cooldown
	if (AtkCldn > 0)
		--AtkCldn;

	// The enemy will detect player if it is within field of view.
	// Make sure to implement pigman like warning
	if (Theta < 60)
	{
		SetActorRotation(PosDiff.ToOrientationRotator());
		Warn();

		if (magnitude < 300)
		{
			Attack(GetWorld()->GetFirstPlayerController()->GetPawn());
		}
		else
			Walk(true);
		ThisPos = GetActorLocation();

	}
	else
	{
		// a random number deciding to randomly turn
		unsigned int RndNum = std::chrono::time_point_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now()).time_since_epoch().count() % 3600;

		if (RndNum == 0)
		{
			float pitch = RndNum / 10, yaw = std::chrono::time_point_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now()).time_since_epoch().count() % 360;
			SetActorRotation({ pitch, yaw, 0.0f });
		}
	}

	if (WarnInited && WarnTimer == 0)
	{
		// Get all of the actors and warn them if they are also a Skulkin
		WarnInited = false;

		TArray<AActor*>actors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASerpentine::StaticClass(), actors);

		for (auto begin = actors.begin(); begin != actors.end(); ++begin)
		{
			if (*begin != this)
			{
				// cast the reference
				ASerpentine& sk = dynamic_cast<ASerpentine&>(**begin);
				if ((PlayerPos - sk.GetActorLocation()).Size() < 25000)
					sk.BeWarned(PlayerPos - sk.GetActorLocation());
			}
		}

	}

	// Decrease the warning timer
	if (WarnInited && WarnTimer > 0)
		--WarnTimer;

	// Setting the actor location will cause the rotation to update, and vice versa
	// Setting the actor rotation will do nothing if location is not set
	SetActorLocation(ThisPos);

}

// Warns other enemies of player
void ASerpentine::Warn()
{
	if (!WarnInited)
	{
		WarnTimer = 300;
		WarnInited = true;
	}
}

void ASerpentine::BeWarned(const FVector& PlayerPos)
{
	SetActorRotation(PlayerPos.ToOrientationRotator());
	SetActorLocation(GetActorLocation());
}
