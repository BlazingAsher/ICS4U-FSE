// Copyright (c) 2020 David Hui and Kevin Zhang. ALL RIGHTS RESERVED.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
//#include <string>
#include "Door.generated.h"

UCLASS()
class ICS4UFSE_CPP_API ADoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Opens or closes the door
	void ToggleDoor();

	// Getters and setters
	bool Opened();
	void Opened(bool b);

	bool Animating();
	void Animating(bool b);

	/*std::string OpenDirection();
	void OpenDirection(const std::string& dir);
	void OpenDirection(std::string&& dir);*/

	float AnimDegrees();
	void AnimDegrees(float f);

	FVector DoorPivot();
	void DoorPivot(const FVector&piv);

protected:
	// Is the door already open
	bool IsOpen;
	
	// Is the door being opened or closed
	bool IsAnimating;

	// Direction for opening the door
	UPROPERTY(EditAnywhere)
	bool YawPos;

	// How many degrees the door turned
	float DegsAnimated;

	UPROPERTY(EditAnywhere)
	// The most that the door will turn
	float MaxTurn;

	UPROPERTY(EditAnywhere)
	// The weight determines how fast the door turns
	float Weight;

	UPROPERTY(EditAnywhere)
	// The point where the door is turned about
	FVector Pivot;

};
