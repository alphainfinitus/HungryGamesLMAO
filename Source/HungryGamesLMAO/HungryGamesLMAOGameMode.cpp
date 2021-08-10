// Copyright Epic Games, Inc. All Rights Reserved.

#include "HungryGamesLMAOGameMode.h"
#include "HungryGamesLMAOHUD.h"
#include "Player/FirstPersonCharacter.h"
#include "UObject/ConstructorHelpers.h"

AHungryGamesLMAOGameMode::AHungryGamesLMAOGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Dynamic/Character/Behaviour/Character"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AHungryGamesLMAOHUD::StaticClass();
}
