// Copyright (c) 2020 David Hui and Kevin Zhang. ALL RIGHTS RESERVED.


#include "ArmourItem.h"
#include "Components/BoxComponent.h"
#include <Runtime\Engine\Classes\Engine\Engine.h>
#include <ICS4UFSE_CPP\ICS4UFSE_CPPCharacter.h>

// Sets default values
AArmourItem::AArmourItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyMesh"));
	RootComponent = MyMesh;

	MyBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("MyBoxComponent"));
	MyBoxComponent->InitBoxExtent(FVector(50, 50, 50));
	MyBoxComponent->SetCollisionProfileName("Trigger");
	MyBoxComponent->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AArmourItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AArmourItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AICS4UFSE_CPPCharacter& player = dynamic_cast<AICS4UFSE_CPPCharacter&>(*GetWorld()->GetFirstPlayerController()->GetPawn());
	if ((player.GetActorLocation() - GetActorLocation()).Size() < 150)
	{
		player.PlayerArmour.Hardness(player.PlayerArmour.Hardness() + HardImpr);
		player.PlayerArmour.Toughness(player.PlayerArmour.Toughness() + ToughImpr);
		Destroy();
	}

}