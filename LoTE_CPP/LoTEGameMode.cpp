// Copyright Epic Games, Inc. All Rights Reserved.

#include "LoTEGameMode.h"
#include "LoTEPlayerController.h"
#include "LoTECharacter.h"
#include "UObject/ConstructorHelpers.h"

ALoTEGameMode::ALoTEGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ALoTEPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}