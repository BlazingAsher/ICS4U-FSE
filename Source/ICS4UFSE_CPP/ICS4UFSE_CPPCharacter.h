// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TimerManager.h"
#include "Armour.h"
#include "DmgType.h"
#include <ICS4UFSE_CPP\PainVolume.h>
#include <ICS4UFSE_CPP\ParticleSpawner.h>
#include <ICS4UFSE_CPP\SpecialAttack.h>
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float MaxHealth;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float playerHealth;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float ArmourHardness;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float ArmourToughness;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		int attackState;

	UPROPERTY(BlueprintReadOnly)
		float playerEnergy;

	UPROPERTY(BlueprintReadOnly)
		int exp;

	UPROPERTY(BlueprintReadOnly)
		float ExpPercent;

	UPROPERTY(BlueprintReadOnly)
		int ComputedLvl;

	UPROPERTY(BlueprintReadOnly)
		int PortalProgress;

	UPROPERTY(BlueprintReadOnly)
		int SpecialAttackProgress = 3;

	UPROPERTY(BlueprintReadOnly)
		TEnumAsByte<SpecialAttack> SelectedSpecial = SpecialAttack::None;

	UPROPERTY(EditDefaultsOnly, Category = "ActorSpawning")
		TSubclassOf<APainVolume> PainVolumeBP;

	UPROPERTY(EditDefaultsOnly, Category = "ActorSpawning")
		TSubclassOf<AParticleSpawner> SpinParticleSpawner;

	UPROPERTY(EditDefaultsOnly, Category = "ActorSpawning")
		TSubclassOf<AParticleSpawner> TornadoParticleSpawner;

	UPROPERTY(EditDefaultsOnly, Category = "ActorSpawning")
		TSubclassOf<AParticleSpawner> ElementalParticleSpawner;

	FVector Launch;

	float LaunchIncr, LaunchIncrIncr;

	FArmour PlayerArmour;

	

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
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

protected:
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

	UFUNCTION()
	int GetExp();

	UFUNCTION()
	int GetLvl();

	UFUNCTION()
	int GetExpToNextLvl();

	UFUNCTION()
	int GetNextLvlRequiredExp();

	UFUNCTION()
	void AddExp(int x);

	UFUNCTION()
	float GetExpPercent();

	UFUNCTION()
	int GetComputedLvl();

	UFUNCTION()
	void AddPortalProgress();

	UFUNCTION()
	bool HasPortal();

	UFUNCTION()
	void Heal(float hp);

	UFUNCTION()
	void LaunchPlayer(FVector LaunchDirection);

	UFUNCTION()
		void AddSpell();

	UFUNCTION()
		void CycleSpell();

	UFUNCTION()
		void SetSpell(SpecialAttack toBeSet);

};
