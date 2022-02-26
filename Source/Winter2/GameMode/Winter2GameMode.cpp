// Copyright Epic Games, Inc. All Rights Reserved.

#include "Winter2GameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "Winter2/Widgets/Winter2HUD.h"

AWinter2GameMode::AWinter2GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
	// use our custom HUD class
	HUDClass = AWinter2HUD::StaticClass();
}
