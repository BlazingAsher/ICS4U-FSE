// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "ICS4UFSE_CPPGameMode.h"
#include "ICS4UFSE_CPPCharacter.h"
#include "UObject/ConstructorHelpers.h"

AICS4UFSE_CPPGameMode::AICS4UFSE_CPPGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
