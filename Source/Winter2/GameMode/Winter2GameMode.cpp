// Copyright Epic Games, Inc. All Rights Reserved.

#include "Winter2GameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "Winter2/Managers/MyGameInstance.h"
#include "Winter2/Widgets/Winter2HUD.h"
#include "Winter2/Actor/MyPlayerController.h"

AWinter2GameMode::AWinter2GameMode()
	: Super()
{

	PlayerControllerClass = AMyPlayerController::StaticClass();

	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
	// use our custom HUD class
	HUDClass = AWinter2HUD::StaticClass();
	m_fTimePassed = 0;
	
	m_fGameWinTime = 600;
	
//#if !UE_BUILD_SHIPPING
//	m_fGameWinTime = 20;
//#endif
}

void AWinter2GameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	m_fTimePassed+=DeltaSeconds;

	if(m_fTimePassed >= m_fGameWinTime)
	{
		SetActorTickEnabled(false);

		UMyGameInstance::Get->WinGame();
	}
}

float AWinter2GameMode::GetTimePassed()
{
	return m_fTimePassed;
}

float AWinter2GameMode::GetWinMaxTime()
{
	return m_fGameWinTime;
}

float AWinter2GameMode::GetTimePercentOne()
{
	return GetTimePassed() / m_fGameWinTime;
}

FString AWinter2GameMode::UpdateTimePassed()
{
	int Minute = m_fTimePassed;

	Minute /= 60.0f;

	int Sec = m_fTimePassed;

	Sec = Sec % 60;
	
	FString Str = FString::Printf(TEXT("%d:%d"),Minute,Sec);

	return Str;
}