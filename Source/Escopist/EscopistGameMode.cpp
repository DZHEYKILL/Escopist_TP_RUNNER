// Copyright Epic Games, Inc. All Rights Reserved.

#include "EscopistGameMode.h"
#include "EscopistCharacter.h"
#include "UObject/ConstructorHelpers.h"

AEscopistGameMode::AEscopistGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
