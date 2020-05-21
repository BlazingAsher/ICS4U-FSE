// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TimerManager.h"
#include "Armour.h"
#include "DmgType.h"
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

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float playerHealth;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float playerArmour;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
		int attackState;

	UPROPERTY(BlueprintReadOnly)
		float playerEnergy;

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

	/* Left click handler */
	void OnAttack();

	/* End left click handler */
	void EndAttack();

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

	Armour PlayerArmour;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	/** Apply damage to the player */
	UFUNCTION()
	void ApplyDamage(float Damage);

	/** Add attack energy to the player **/
	UFUNCTION()
	void AddEnergy(float Energy);

	/** Remove attack energy from the player **/
	UFUNCTION()
	void RemoveEnergy(float Energy);
};

