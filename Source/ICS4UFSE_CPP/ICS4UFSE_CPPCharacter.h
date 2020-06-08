// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TimerManager.h"
#include "Armour.h"
#include "DmgType.h"
#include <ICS4UFSE_CPP\Enemy.h>
#include <ICS4UFSE_CPP\PainVolume.h>
#include <ICS4UFSE_CPP\ParticleSpawner.h>
#include <ICS4UFSE_CPP\SpecialAttack.h>
#include "Sound/SoundCue.h"
#include "ICS4UFSE_CPPCharacter.generated.h"

UCLASS(config=Game)
class AICS4UFSE_CPPCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
public:
	AICS4UFSE_CPPCharacter();

	// Number of portal pieces required
	const static int PORTAL_NUM_PIECES = 4;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	// Max player health
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float MaxHealth;

	// Curent player health
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float playerHealth;

	// Armour hardness
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float ArmourHardness;

	// Armour toughness
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float ArmourToughness;

	// Current player attack state (used for animations)
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		int attackState;

	// Current player energy
	UPROPERTY(BlueprintReadOnly)
		float playerEnergy;

	// Curent player exp
	UPROPERTY(BlueprintReadOnly)
		int exp;

	// Current player level exp percentage
	UPROPERTY(BlueprintReadOnly)
		float ExpPercent;

	// Current player computed level
	UPROPERTY(BlueprintReadOnly)
		int ComputedLvl;

	// Current player level progress
	UPROPERTY(BlueprintReadOnly)
		int PortalProgress;

	// Current player special attack level
	UPROPERTY(EditInstanceOnly)
		int SpecialAttackProgress = 0;

	// Current player selected special attack
	UPROPERTY(BlueprintReadOnly)
		TEnumAsByte<SpecialAttack> SelectedSpecial = SpecialAttack::None;

	// Reference to pain volume to spawn during special attacks
	UPROPERTY(EditDefaultsOnly, Category = "ActorSpawning")
		TSubclassOf<APainVolume> PainVolumeBP;

	// Spinjitsu particle
	UPROPERTY(EditDefaultsOnly, Category = "ActorSpawning")
		TSubclassOf<AParticleSpawner> SpinParticleSpawner;

	// Tornado of creation particle
	UPROPERTY(EditDefaultsOnly, Category = "ActorSpawning")
		TSubclassOf<AParticleSpawner> TornadoParticleSpawner;
	
	// Elemental attack particle
	UPROPERTY(EditDefaultsOnly, Category = "ActorSpawning")
		TSubclassOf<AParticleSpawner> ElementalParticleSpawner;

	// Punching sound
	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
		USoundCue* PunchSound;

	// Special attack sound
	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
		USoundCue* SpecialSound;

	// Item pickup sound
	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
		USoundCue* PickupSound;

	// Death found
	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
		USoundCue* DeathSound;

	// Player launch direction
	FVector Launch;

	// Used for launch acceleration
	float LaunchIncr, LaunchIncrIncr;

	// Current player armour
	FArmour PlayerArmour;

	// The actor the player is stuck to
	AActor* StuckTo;
	
	// Whether the player is hypnotized
	bool IsHypnotized;

	// Where the player last was when it was hypnotized (hypnotized teleport origin)
	FVector HTPO;

	// Player respawn point
	UPROPERTY(EditAnywhere)
	FVector SpawnPoint;

protected:

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	void BeginPlay();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

	void Tick(float DeltaTime)override;

	/* Left click handler */
	void OnAttack();

	/* End left click handler */
	void EndAttack();

	/* Special attack handler*/
	void OnSpecialAttack();

	/* Ed special attack handler */
	void EndSpecialAttack();

	/* Right click handler */
	void OnUse();

	/* End right click handler */
	void EndUse();

	/* Crouch handler */
	void OnCrouch();

	/* Uncrouch handler */
	void EndCrouch();

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

protected:
	// Timer handlers
	FTimerHandle EnergyRegenTimerHandle;
	FTimerDelegate EnergyRegenTimerDelegate;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	/** Apply damage to the player */
	UFUNCTION()
		void ApplyDamage(float Damage, DmgType Type = DmgType::DmgMelee, AActor* src = nullptr);

	/** Add attack energy to the player **/
	UFUNCTION()
	void AddEnergy(float Energy);

	/** Remove attack energy from the player **/
	UFUNCTION()
	void RemoveEnergy(float Energy);

	// Get player exp
	UFUNCTION()
	int GetExp();

	// Get player level
	UFUNCTION()
	int GetLvl();

	// Get amount of exp required to move to next level
	UFUNCTION()
	int GetExpToNextLvl();

	// Calculates the exp difference between your next level and your current level
	UFUNCTION()
	int GetNextLvlRequiredExp();

	// Give player exp
	UFUNCTION()
	void AddExp(int x);

	// Get percent of exp
	UFUNCTION()
	float GetExpPercent();

	// Get the player's computed level
	UFUNCTION()
	int GetComputedLvl();

	// Add player portal progress
	UFUNCTION()
	void AddPortalProgress();

	// Whether the player has spawned the portal in
	UFUNCTION()
	bool HasPortal();

	// Heal the player
	UFUNCTION()
	void Heal(float hp);

	// Launch the player into the air
	UFUNCTION()
	void LaunchPlayer(FVector LaunchDirection);

	// Level up the player's special abilities
	UFUNCTION()
		void AddSpell();

	// Cycle through currently selected spell
	UFUNCTION()
		void CycleSpell();

	// Set the currently selected spell
	UFUNCTION()
		void SetSpell(SpecialAttack toBeSet);

	// Hypnotize the player
	void BeHypnotized(const AEnemy& enemy);

	// Respawn the player
	UFUNCTION()
		void Respawn();

	// Play the item pickup sound
	UFUNCTION()
		void PlayPickupSound();

};
