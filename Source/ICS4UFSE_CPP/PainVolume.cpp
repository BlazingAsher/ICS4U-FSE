// Fill out your copyright notice in the Description page of Project Settings.

#include "PainVolume.h"

// Sets default values
APainVolume::APainVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	HitArea = CreateDefaultSubobject<USphereComponent>(TEXT("HitArea"));
	HitArea->SetSphereRadius(75.0f);
	RootComponent = HitArea;

	HitArea->OnComponentBeginOverlap.AddDynamic(this, &APainVolume::OnOverlapBegin);
}

// Called when the game starts or when spawned
void APainVolume::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APainVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APainVolume::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AICS4UFSE_CPPCharacter* otherGuyCharacter = Cast<AICS4UFSE_CPPCharacter>(OtherActor);

	otherGuyCharacter->ApplyDamage(0.05f);

	
}