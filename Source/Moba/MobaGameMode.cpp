// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "Moba.h"
#include "MobaGameMode.h"
#include "MobaPlayerController.h"
#include "MobaCharacter.h"

AMobaGameMode::AMobaGameMode()
{
	/*
	// use our custom PlayerController class/*
	PlayerControllerClass = AMobaPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	*/
}