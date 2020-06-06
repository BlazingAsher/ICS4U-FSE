// Fill out your copyright notice in the Description page of Project Settings.

#include "PainVolume.h"
#include <ICS4UFSE_CPP/Enemy.h>
#include "Engine/Engine.h"
#include "UObject/UObjectIterator.h"

// Sets default values
APainVolume::APainVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set up the mesh and components
	MyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyMesh"));
	RootComponent = MyMesh;

	MySphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("MySphereComponent"));
	MySphereComponent->InitSphereRadius(50);
	MySphereComponent->SetCollisionProfileName("Trigger");
	MySphereComponent->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void APainVolume::BeginPlay()
{
	Super::BeginPlay();

	// Register overlap listener
	MySphereComponent->OnComponentBeginOverlap.AddDynamic(this, &APainVolume::OnOverlapBegin);

	// Save a reference to the player so that it exp can be given
	SpawnedBy = GetWorld()->GetFirstPlayerController()->GetPawn();

	// Timer handles
	FTimerHandle DamageHandle;
	FTimerHandle OutHandle;

	// Register damage and self-destruction timers
	GetWorld()->GetTimerManager().SetTimer(OutHandle, this, &APainVolume::DefaultDestroy, Lifespan);
	GetWorld()->GetTimerManager().SetTimer(DamageHandle, this, &APainVolume::DamageTick, DamageTickTime, true, 0);
}

// Called every frame
void APainVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	// Follow the player
	SetActorLocation(SpawnedBy->GetActorLocation());
}

// Called when an actor overlaps with the Pain VL
void APainVolume::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Attack(OtherActor);
}

// Called every damage tick
void APainVolume::DamageTick()
{
	// Debug message
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-5, .5f, FColor::Blue, "Damage tick!");
	}

	// Get all Enemies that are overlapping
	TArray<AActor*> overlapping;
	GetOverlappingActors(overlapping, TSubclassOf<AEnemy>(AEnemy::StaticClass()));

	// Apply damage
	for (auto& Enemy : overlapping) {
		Attack(Enemy);
	}

}

// Attack the given Actor
void APainVolume::Attack(class AActor* Target)
{
	// Cast to enemy and apply damage
	if (dynamic_cast<AEnemy*>(Target)) {
		((AEnemy*)Target)->ApplyDamage(DamageAmt, DmgType::DmgMelee, SpawnedBy);
	}
}

// Utility; Destroy() without any parameters
void APainVolume::DefaultDestroy() {
	Destroy();
}

// Set the damage of the Pain VL
void APainVolume::SetDamage(float damage) {
	DamageAmt = damage;
}