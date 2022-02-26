#include "MyGameInstance.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Winter2/MyLib.h"

UMyGameInstance* UMyGameInstance::Get = nullptr;

void UMyGameInstance::Init()
{
	Super::Init();
	
	Get = this;

	m_ZoneMoveManager = NewObject<ULevelManager>(this);
	m_SpawnManager = NewObject<USpawnManager>(this);
	m_PlayerStatManager = NewObject<UPlayerStatusManager>(this);
}

void UMyGameInstance::LoadComplete(const float LoadTime, const FString& MapName)
{
	if(MapName!=TEXT("InitLevel"))
	{
		if(m_ZoneMoveManager->IsGameStart())
		{
			m_ZoneMoveManager->OnOpenWorldLevelComplete();
		}
	}
}

void UMyGameInstance::StartGame()
{
	m_ZoneMoveManager->OpenMyLevel(TEXT("TestLeval"));

	UKismetSystemLibrary::ControlScreensaver(false);
}

void UMyGameInstance::ExitGame()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), UMyLib::GetPlayerCon(), EQuitPreference::Quit, true);
}
