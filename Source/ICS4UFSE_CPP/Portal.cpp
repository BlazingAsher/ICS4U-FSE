// Copyright (c) 2020 David Hui and Kevin Zhang. ALL RIGHTS RESERVED.


#include "Portal.h"
#include "Kismet/GameplayStatics.h"
#include <ICS4UFSE_CPP\ICS4UFSE_CPPCharacter.h>
#include "Engine/Engine.h"

// Sets default values
APortal::APortal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyMesh"));
	RootComponent = MyMesh;

//	MyBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("MyBoxComponent"));
//	MyBoxComponent->InitBoxExtent(FVector(50, 50, 50));
//	MyBoxComponent->SetCollisionProfileName("Trigger");
//	MyBoxComponent->SetupAttachment(RootComponent);
	PortalComponent = CreateDefaultSubobject<USphereComponent>(TEXT("PortalComponent"));
	PortalComponent->InitSphereRadius(51);
	PortalComponent->SetCollisionProfileName(TEXT("Trigger"));
	PortalComponent->SetupAttachment(RootComponent);

	OnMaterial = CreateDefaultSubobject<UMaterial>(TEXT("OnMaterial"));
	OffMaterial = CreateDefaultSubobject<UMaterial>(TEXT("OffMaterial"));

}

// Called when the game starts or when spawned
void APortal::BeginPlay()
{
	Super::BeginPlay();
	PortalComponent->OnComponentBeginOverlap.AddDynamic(this, &APortal::OnOverlapBegin);

	MyMesh->SetMaterial(0, OffMaterial);
	
}

// Called every frame
void APortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Fired when another Actor overlaps the Portal Component
void APortal::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Null pointer and self check, also make sure that the actor is the player and not an NPC
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && GetWorld()->GetFirstPlayerController()->GetPawn() == OtherActor)
	{
		if (dynamic_cast<AICS4UFSE_CPPCharacter*>(OtherActor)) {
			if (((AICS4UFSE_CPPCharacter*)OtherActor)->HasPortal()) {
				UGameplayStatics::PlaySound2D(GetWorld(), TeleportSound, 1.0f, 1.0f);
				OtherActor->SetActorLocation(FVector(-27310.0, 65120.0, 210.0));
			}
			else {
				// launches the player if the portal is not active yet
				AICS4UFSE_CPPCharacter& player = dynamic_cast<AICS4UFSE_CPPCharacter&>(*OtherActor);
				player.LaunchPlayer((FVector(0, 0, 1) + player.GetActorLocation() - GetActorLocation()) * 10);

				if (GEngine) {
					GEngine->AddOnScreenDebugMessage(-10, 5.0f, FColor::Red, "This portal is not yet active!");
				}
			}
		}
			

	}
}

void APortal::ActivatePortal() {
	MyMesh->SetMaterial(0, OnMaterial);
	FActorSpawnParameters SpawnParams;
	GetWorld()->SpawnActor<AParticleSpawner>(ParticleSpawner, GetTransform(), SpawnParams);
}