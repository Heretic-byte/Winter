#include "LevelManager.h"

#include "BUITween.h"
#include "MyGameInstance.h"
#include "Kismet/GameplayStatics.h"

void ULevelManager::OpenMyLevel(FName mapLevelName)
{
	m_MapID = mapLevelName;
	
	UGameplayStatics::OpenLevel(this,m_MapID);
}

void ULevelManager::OnOpenWorldLevelComplete()
{
	UBUITween::Shutdown();
	
	//UMyGameInstance::Get->m_SpawnManager->SetSpawnActors(m_ZoneData->m_SpawnDataNpc);

	//m_OnLvelMoveComp.Broadcast(m_ZoneData->m_ShowingName);
}

bool ULevelManager::IsGameStart()
{
	return true;
}

const FName& ULevelManager::GetMapID() const
{
	return m_MapID;
}
