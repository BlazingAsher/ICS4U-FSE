// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "ICS4UFSE_CPPCharacter.h"
#include <algorithm>
#include <cmath>
#include "Kismet/GameplayStatics.h"
#include "Door.h"
#include "DistPred.h"
#include "Enemy.h"
#include "Templates/SubclassOf.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/Engine.h"
#include "UObject/UObjectIterator.h"
#include <ICS4UFSE_CPP\Portal.h>

//////////////////////////////////////////////////////////////////////////
// AICS4UFSE_CPPCharacter

AICS4UFSE_CPPCharacter::AICS4UFSE_CPPCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character
	CameraBoom->bUsePawnControlRotation = false; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	//FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	//FollowCamera->SetupAttachment(GetMesh(), FName("head"));
	//FollowCamera->AttachTo(GetMesh(), FName("head"));
	//FollowCamera->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("head"));

	FollowCamera->bUsePawnControlRotation = true; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character)
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)

	// Set health and armour defaults
	exp = 0;

	MaxHealth = 150.0f;
	playerHealth = MaxHealth;

	ArmourHardness = PlayerArmour.Hardness();
	ArmourToughness = PlayerArmour.Toughness();

	attackState = 0;

	playerEnergy = 0.5f;
}

void AICS4UFSE_CPPCharacter::BeginPlay()
{
	Super::BeginPlay();

	FollowCamera->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("head"));
	FollowCamera->RelativeLocation = FVector(0.000000, 1.000000, 25.000000);  // left,right - up,down - fwd, back
	FollowCamera->RelativeRotation = FRotator(90.000000, 0.000000, -90.000000);

	EnergyRegenTimerDelegate.BindUFunction(this, FName("AddEnergy"), 0.1f);
	GetWorldTimerManager().SetTimer(EnergyRegenTimerHandle, EnergyRegenTimerDelegate, 5.f, true);
}

//////////////////////////////////////////////////////////////////////////
// Input


void AICS4UFSE_CPPCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &AICS4UFSE_CPPCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AICS4UFSE_CPPCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AICS4UFSE_CPPCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AICS4UFSE_CPPCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AICS4UFSE_CPPCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AICS4UFSE_CPPCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AICS4UFSE_CPPCharacter::OnResetVR);

	// Mouse controls
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &AICS4UFSE_CPPCharacter::OnAttack);
	PlayerInputComponent->BindAction("Attack", IE_Released, this, &AICS4UFSE_CPPCharacter::EndAttack);
	PlayerInputComponent->BindAction("Use", IE_Pressed, this, &AICS4UFSE_CPPCharacter::OnUse);
	PlayerInputComponent->BindAction("Use", IE_Released, this, &AICS4UFSE_CPPCharacter::EndUse);

	// Special Attack
	PlayerInputComponent->BindAction("SpecialAttack", IE_Pressed, this, &AICS4UFSE_CPPCharacter::OnSpecialAttack);
	PlayerInputComponent->BindAction("SpecialAttack", IE_Released, this, &AICS4UFSE_CPPCharacter::EndSpecialAttack);

	// Cycle special attacks
	PlayerInputComponent->BindAction("ChangeSpecial", IE_Pressed, this, &AICS4UFSE_CPPCharacter::CycleSpell);

	// Crouching
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AICS4UFSE_CPPCharacter::OnCrouch);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &AICS4UFSE_CPPCharacter::EndCrouch);
}

void AICS4UFSE_CPPCharacter::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AICS4UFSE_CPPCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	Jump();
}

void AICS4UFSE_CPPCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	StopJumping();
}

void AICS4UFSE_CPPCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (LaunchIncr < 60 * LaunchIncrIncr)
	{
		SetActorLocation(GetActorLocation() + Launch * LaunchIncr);
		LaunchIncr += LaunchIncrIncr;
	}
}

void AICS4UFSE_CPPCharacter::OnAttack()
{
	attackState = 1;
}

void AICS4UFSE_CPPCharacter::OnSpecialAttack()
{
	int specialID = SelectedSpecial;
	float requiredEnergy = (specialID + 1) / 4.f;
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-18, 5.0f, FColor::Red, FString::FromInt(specialID));
		GEngine->AddOnScreenDebugMessage(-37, 5.0f, FColor::Red, FString::FromInt(requiredEnergy*100));
	}
	if (SelectedSpecial != SpecialAttack::None && playerEnergy >= requiredEnergy && PainVolumeBP) {
		attackState = 5;
		FVector volumeSpawnLocation = GetActorLocation() + GetActorForwardVector() * 250;
		FActorSpawnParameters SpawnParams;
		APainVolume* PainVLInstance = GetWorld()->SpawnActor<APainVolume>(PainVolumeBP, volumeSpawnLocation, FRotator(), SpawnParams);
		//GetWorld()->SpawnActor<APainVolume>(PainVolumeBP, GetTransform(), SpawnParams);

		TSubclassOf<AParticleSpawner> SpawnerClass;

		if (SelectedSpecial == SpecialAttack::Spin) {
			SpawnerClass = SpinParticleSpawner;
		}
		else if (SelectedSpecial == SpecialAttack::Tornado) {
			SpawnerClass = TornadoParticleSpawner;
		}
		else if (SelectedSpecial == SpecialAttack::Elemental) {
			SpawnerClass = ElementalParticleSpawner;
		}

		PainVLInstance->SetDamage(specialID * 15);

		if (SpawnerClass) {
			AParticleSpawner* ParticleSpawnerInstance = GetWorld()->SpawnActor<AParticleSpawner>(SpawnerClass, volumeSpawnLocation, FRotator(), SpawnParams);
			ParticleSpawnerInstance->SetFollow(this);
			if (GEngine) {
				GEngine->AddOnScreenDebugMessage(-12, 5.0f, FColor::Red, "spawned particle");
			}
		}

		RemoveEnergy(requiredEnergy);
	}

	//if (playerEnergy > 0.7f && PainVolumeBP) {
	//	attackState = 5;
	//	// Spawn the painvolume at its radius away so that character is in the center
	//	FVector volumeSpawnLocation = GetActorLocation() + GetActorForwardVector() * 250;
	//	FActorSpawnParameters SpawnParams;
	//	GetWorld()->SpawnActor<APainVolume>(PainVolumeBP, volumeSpawnLocation, FRotator(), SpawnParams);
	//	RemoveEnergy(0.7f);
	//}
	//else if (!PainVolumeBP) {
	//	if (GEngine) {
	//		GEngine->AddOnScreenDebugMessage(-9, 5.0f, FColor::Red, "No pain volume!");
	//	}
	//}
	
}

void AICS4UFSE_CPPCharacter::EndSpecialAttack()
{
	attackState = 0;
}

void AICS4UFSE_CPPCharacter::EndAttack()
{

	attackState = 0;

	TArray<AActor*>actors;
	AEnemy* aep;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), TSubclassOf<AActor>(AEnemy::StaticClass()), actors);

	FVector EnemyPos, ThisPos = GetActorLocation(), PosDiff;

	for (AActor* actptr : actors)
	{
		aep = (AEnemy*)actptr;
		
		EnemyPos = aep->GetActorLocation();
		PosDiff = EnemyPos - ThisPos;

		if (PosDiff.Size() < 300 && std::acos((PosDiff | GetActorRotation().Vector()) / PosDiff.Size()) < 3.1415926535897932 / 3)
		{
			// deal damage to the enemy
			//aep->ApplyDamage(GetLvl() + 1, DmgType::DmgMelee, this);
			aep->ApplyDamage(GetLvl() * 15 + 30, DmgType::DmgMelee, this);
			// knock the enemy back a bit
			aep->SetActorRotation(aep->GetActorRotation());
			aep->SetActorLocation(FVector{ 0.0f, 0.0f, 2.0f } + PosDiff / PosDiff.Size() * (PosDiff.Size() + 10) + ThisPos);

		}

	}

}

void AICS4UFSE_CPPCharacter::OnUse()
{

}

void AICS4UFSE_CPPCharacter::EndUse()
{

	TArray<AActor*>actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADoor::StaticClass(), actors);

	// Get the closest door
	actors.Sort(DistPred(GetActorLocation()));
	ADoor& closest = (ADoor&)**actors.begin();

	if (std::acos((((closest.GetActorLocation() - GetActorLocation()) | GetActorRotation().Vector()) / (closest.GetActorLocation() - GetActorLocation()).Size()))< 3.1415926535897932 / 3 && (closest.GetActorLocation() - GetActorLocation()).Size() < 300)
		closest.ToggleDoor();

}

void AICS4UFSE_CPPCharacter::OnCrouch()
{
	Crouch();
}

void AICS4UFSE_CPPCharacter::EndCrouch()
{
	UnCrouch();
}

void AICS4UFSE_CPPCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AICS4UFSE_CPPCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AICS4UFSE_CPPCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AICS4UFSE_CPPCharacter::MoveRight(float Value)
{
	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void AICS4UFSE_CPPCharacter::ApplyDamage(float Damage, DmgType Type, AActor* src)
{

	if (Type < DmgType::DmgFall)
	{
		// apply armour damage
		playerHealth -= PlayerArmour - Damage;
		if (playerHealth < 0)
			playerHealth = 0;
	}
	else
		playerHealth = std::max(0.0f, playerHealth - Damage);
	
	ArmourHardness = PlayerArmour.Hardness();
	ArmourToughness = PlayerArmour.Toughness();

}

void AICS4UFSE_CPPCharacter::AddEnergy(float Energy) {
	playerEnergy = playerEnergy + Energy <= 1.0f ? playerEnergy + Energy : 1.0f;
//	if (GEngine) {
//		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, "Added energy!");
//	}
}

void AICS4UFSE_CPPCharacter::RemoveEnergy(float Energy) {
	playerEnergy = playerEnergy - Energy >= 0.0f ? playerEnergy - Energy : 0.0f;
//	if (GEngine) {
//		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, "Removed energy!");
//	}
}

int AICS4UFSE_CPPCharacter::GetExp()
{
	return exp;
}

int AICS4UFSE_CPPCharacter::GetLvl()
{
	using namespace std;
	double x = exp;
	if (x == 0)
		return ComputedLvl = 0;
	else
		return ComputedLvl = (int)floor(cbrt(x / 2 + sqrt(27 * x * x - 4) / 6 / sqrt(3)) + cbrt(x / 2 - sqrt(27 * x * x - 4) / 6 / sqrt(3)) - 1);
}

int AICS4UFSE_CPPCharacter::GetExpToNextLvl()
{
	int lvl = GetLvl() + 1;
	return lvl * lvl * lvl + 3 * lvl * lvl + 2 * lvl - exp;
}

int AICS4UFSE_CPPCharacter::GetNextLvlRequiredExp()
{
	int lvl = GetLvl();
	return 3 * lvl * lvl + 9 * lvl + 6;
}

void AICS4UFSE_CPPCharacter::AddExp(int x)
{
	exp += x;

	ExpPercent = 1 - (float)GetExpToNextLvl() / GetNextLvlRequiredExp();
}

float AICS4UFSE_CPPCharacter::GetExpPercent()
{
	return ExpPercent;
}

int AICS4UFSE_CPPCharacter::GetComputedLvl()
{
	return ComputedLvl;
}

void AICS4UFSE_CPPCharacter::AddPortalProgress()
{
	PortalProgress += 1;
	if (PortalProgress == AICS4UFSE_CPPCharacter::PORTAL_NUM_PIECES) {
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-2, 5.0f, FColor::Blue, "Portal spawning!");
		}

		for (TObjectIterator<APortal> Itr; Itr; ++Itr)
		{
			if (Itr->IsA(APortal::StaticClass()))
			{
				Itr->ActivatePortal();
			}
		}
	}
}

bool AICS4UFSE_CPPCharacter::HasPortal() {
	return PortalProgress == AICS4UFSE_CPPCharacter::PORTAL_NUM_PIECES;
}

void AICS4UFSE_CPPCharacter::Heal(float hp)
{
	playerHealth += hp;
	if (playerHealth > MaxHealth)
		playerHealth = MaxHealth;
}

void AICS4UFSE_CPPCharacter::LaunchPlayer(FVector LaunchDirection)
{
	Launch = LaunchDirection / LaunchDirection.Size();
	LaunchIncr = LaunchDirection.Size() / 3600;
	LaunchIncrIncr = LaunchDirection.Size() / 1800;
}

void AICS4UFSE_CPPCharacter::AddSpell() {
	SpecialAttackProgress++;
}

void AICS4UFSE_CPPCharacter::CycleSpell() {
	if (SelectedSpecial == SpecialAttack::None && SpecialAttackProgress > 0) {
		SelectedSpecial = SpecialAttack::Spin;
	}
	else if (SelectedSpecial == SpecialAttack::Spin && SpecialAttackProgress > 1) {
		SelectedSpecial = SpecialAttack::Tornado;
	}
	else if (SelectedSpecial == SpecialAttack::Tornado && SpecialAttackProgress > 2) {
		SelectedSpecial = SpecialAttack::Elemental;
	}
	else if (SelectedSpecial == SpecialAttack::Elemental) {
		SelectedSpecial = SpecialAttack::Spin;
	}
	else {
		SelectedSpecial = SpecialAttack::None;
	}

	if (GEngine) {
		int attackID = SelectedSpecial;
		GEngine->AddOnScreenDebugMessage(-14, 5.0f, FColor::Green, "Changed special attack to " + FString::FromInt(attackID));
	}
}

void AICS4UFSE_CPPCharacter::SetSpell(SpecialAttack toBeSet) {
	SelectedSpecial = toBeSet;
}