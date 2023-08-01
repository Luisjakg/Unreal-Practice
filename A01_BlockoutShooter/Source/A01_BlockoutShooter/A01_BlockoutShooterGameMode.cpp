// Copyright Epic Games, Inc. All Rights Reserved.

#include "A01_BlockoutShooterGameMode.h"
#include "A01_BlockoutShooterCharacter.h"
#include "UObject/ConstructorHelpers.h"

AA01_BlockoutShooterGameMode::AA01_BlockoutShooterGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
