// Copyright (c) 2020 David Hui and Kevin Zhang. ALL RIGHTS RESERVED.

#include "SpellLearner.h"

// Sets default values
ASpellLearner::ASpellLearner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set up the mesh and component
	MyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyMesh"));
	RootComponent = MyMesh;

	PortalComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	PortalComponent->InitSphereRadius(50);
	PortalComponent->SetCollisionProfileName(TEXT("Trigger"));
	PortalComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ASpellLearner::BeginPlay()
{
	Super::BeginPlay();

	// Register the listener
	PortalComponent->OnComponentBeginOverlap.AddDynamic(this, &ASpellLearner::OnOverlapBegin);
	
}

// Called every frame
void ASpellLearner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Fired when another Actor overlaps the Spell Learner
void ASpellLearner::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Null pointer and self check, also make sure that the actor is the player and not an NPC
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && GetWorld()->GetFirstPlayerController()->GetPawn() == OtherActor)
	{
		// Cast to the player character, add the spell, and self-destruct
		if (dynamic_cast<AICS4UFSE_CPPCharacter*>(OtherActor)) {
			((AICS4UFSE_CPPCharacter*)OtherActor)->AddSpell();
			((AICS4UFSE_CPPCharacter*)OtherActor)->PlayPickupSound();
			if (GEngine) {
				GEngine->AddOnScreenDebugMessage(-110, 5.0f, FColor::Green, "You learned a new spell!");
			}
			Destroy();
		}


	}
}
