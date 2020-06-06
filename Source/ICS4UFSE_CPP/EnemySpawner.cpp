// Copyright (c) 2020 David Hui and Kevin Zhang. ALL RIGHTS RESERVED.


#include "EnemySpawner.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyMesh"));
	RootComponent = MyMesh;

	PortalComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	PortalComponent->InitSphereRadius(50);
	PortalComponent->SetCollisionProfileName(TEXT("Trigger"));
	PortalComponent->SetupAttachment(RootComponent);
	
}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle spawnerHandle;
	GetWorldTimerManager().SetTimer(spawnerHandle, this, &AEnemySpawner::Spawn, SpawnTickRate);
	
}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemySpawner::Spawn()
{
	FActorSpawnParameters SpawnParameters;
	FVector SpawnLocation = GetActorLocation();

	SpawnLocation.X += (rand() % SpawnRadius * 2) - SpawnRadius;
	SpawnLocation.Y += (rand() % SpawnRadius * 2) - SpawnRadius;

	FRotator SpawnRotation;
	GetWorld()->SpawnActor<AActor>(ToSpawn, SpawnLocation, SpawnRotation, SpawnParameters);
}