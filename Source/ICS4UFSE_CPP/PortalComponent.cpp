// Copyright (c) 2020 David Hui and Kevin Zhang. ALL RIGHTS RESERVED.


#include "PortalComponent.h"
#include "Components/BoxComponent.h"
#include <ICS4UFSE_CPP\ICS4UFSE_CPPCharacter.h>

// Sets default values
APortalComponent::APortalComponent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set up mesh and box component
	MyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyMesh"));
	RootComponent = MyMesh;

	MyBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("MyBoxComponent"));
	MyBoxComponent->InitBoxExtent(FVector(50, 50, 50));
	MyBoxComponent->SetCollisionProfileName("Trigger");
	MyBoxComponent->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void APortalComponent::BeginPlay()
{
	Super::BeginPlay();

	// Register overlap listener
	MyBoxComponent->OnComponentBeginOverlap.AddDynamic(this, &APortalComponent::OnOverlapBegin);
	
}

// Called every frame
void APortalComponent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Fired when another Actor overlaps the Portal Component
void APortalComponent::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Null pointer and self check, also make sure that the actor is the player and not an NPC
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && GetWorld()->GetFirstPlayerController()->GetPawn() == OtherActor)
	{
		// Cast to a player and add portal progress
		if (dynamic_cast<AICS4UFSE_CPPCharacter*>(OtherActor)) {
			((AICS4UFSE_CPPCharacter*)OtherActor)->AddPortalProgress();
			((AICS4UFSE_CPPCharacter*)OtherActor)->PlayPickupSound();
		}



		// Self destruct
		Destroy();
	}
}