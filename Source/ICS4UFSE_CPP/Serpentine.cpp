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
	AlreadySpawned = false;

	void** tmp = reinterpret_cast<void**>(&CMaterial);
	for (int i = 0; i < 8; i++)
		Materials[i] = reinterpret_cast<UMaterial**>(tmp + std::min(4, i));

}

// Called when the game starts or when spawned
void ASerpentine::BeginPlay()
{

	Super::BeginPlay();
	SType = Fangpyre;
	using namespace std::chrono;
	auto ct = high_resolution_clock::now().time_since_epoch();
	long long ns = duration_cast<microseconds>(ct).count() % 8;

	if (ns >= 4)
		SType = SerpentineType::Basic;
	else
	{
		SType = (SerpentineType)(SerpentineType::Basic + ns);
		//TSubclassOf<AParticleSpawner>* TBS = &CEffect + ns;
		TSubclassOf<AParticleSpawner> SpawnerClass;

		if (SType == SerpentineType::Constrictai) {
			SpawnerClass = CEffect;
		}
		else if (SType == SerpentineType::Fangpyre) {
			SpawnerClass = FEffect;
		}
		else if (SType == SerpentineType::Hypnobrai) {
			SpawnerClass = HEffect;
		}
		else if (SType == SerpentineType::Venomari) {
			SpawnerClass = VEffect;
		}
		
		if (SpawnerClass) {
			AParticleSpawner* ParticleReference = GetWorld()->SpawnActor<AParticleSpawner>(SpawnerClass, GetTransform());
			ParticleReference->SetFollow(this);
		}
		
	}
	
}

extern template class TArray<AActor*>;

// Called every frame
void ASerpentine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector PlayerPos = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation(), ThisPos = GetActorLocation();
	FVector PosDiff = PlayerPos - ThisPos;
	float magnitude = PosDiff.Size();

	FVector Facing = GetActorRotation().Vector();
	float Theta = std::acos((Facing | PosDiff) / magnitude) * 180 / 3.1415926535897932;

	// The enemy will detect player if it is within field of view.
	if (magnitude < 2000 && Theta < 60)
	{
		SetActorRotation(PosDiff.ToOrientationRotator());
		//AddControllerYawInput((PosDiff.ToOrientationRotator() - GetActorRotation()).Yaw);
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
			//AddControllerYawInput(yaw - GetActorRotation().Yaw);
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

	if (SType && magnitude < 400)
	{

		// special serpentine attacks
		using namespace std::chrono;
		auto ct = high_resolution_clock::now().time_since_epoch();
		long long ns = duration_cast<microseconds>(ct).count();

		if (ns % 3600 == 1729)
		{

			// cast reference for player type
			AICS4UFSE_CPPCharacter& player = dynamic_cast<AICS4UFSE_CPPCharacter&>(*GetWorld()->GetFirstPlayerController()->GetPawn());
			switch (SType)
			{
			case Constrictai:
				CAttack(player);
				break;
			case Fangpyre:
				FAttack(player);
				break;
			case Hypnobrai:
				HAttack(player);
				break;
			case Venomari:
				VAttack(player);
				break;
			}

		}

	}

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

// Functions for different types of serpentine
void ASerpentine::CAttack(AICS4UFSE_CPPCharacter& player)
{
	player.StuckTo = this;
}

void ASerpentine::FAttack(AICS4UFSE_CPPCharacter& player)
{
	player.ApplyDamage(std::numeric_limits<float>::infinity(), DmgType::DmgPoison);
}

void ASerpentine::HAttack(AICS4UFSE_CPPCharacter& player)
{
	player.BeHypnotized(*this);
}

void ASerpentine::VAttack(AICS4UFSE_CPPCharacter& player)
{
	if (!AlreadySpawned) {
		AlreadySpawned = true;
		GetWorld()->SpawnActor<AActor>(FakeSpawner, GetTransform());
	}
	
}