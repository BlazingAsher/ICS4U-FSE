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
//	HitArea = CreateDefaultSubobject<USphereComponent>(TEXT("HitArea"));
//	HitArea->SetSphereRadius(75.0f);
//	RootComponent = HitArea;

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
	MySphereComponent->OnComponentBeginOverlap.AddDynamic(this, &APainVolume::OnOverlapBegin);
	SpawnedBy = GetWorld()->GetFirstPlayerController()->GetPawn();

	FTimerHandle DamageHandle;
	FTimerHandle OutHandle;

	GetWorld()->GetTimerManager().SetTimer(OutHandle, this, &APainVolume::DefaultDestroy, Lifespan);
	GetWorld()->GetTimerManager().SetTimer(DamageHandle, this, &APainVolume::DamageTick, DamageTickTime, true, 0);
}

// Called every frame
void APainVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	SetActorLocation(SpawnedBy->GetActorLocation());
}

void APainVolume::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Attack(OtherActor);
}

void APainVolume::DamageTick()
{
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-5, .5f, FColor::Blue, "Damage tick!");
	}
	TArray<AActor*> overlapping;
	GetOverlappingActors(overlapping, TSubclassOf<AEnemy>(AEnemy::StaticClass()));

	for (auto& Enemy : overlapping) {
		Attack(Enemy);
	}

}

void APainVolume::Attack(class AActor* Target)
{
	if (dynamic_cast<AEnemy*>(Target)) {
		((AEnemy*)Target)->ApplyDamage(DamageAmt, DmgType::DmgMelee, SpawnedBy);
	}
}

// Destroys the pain volume
void APainVolume::Destroy(bool bNetForce, bool  bShouldModifyLevel)
{
	Super::Destroy(bNetForce, bShouldModifyLevel);
}

void APainVolume::DefaultDestroy() {
	Destroy();
}

void APainVolume::SetDamage(float damage) {
	DamageAmt = damage;
}