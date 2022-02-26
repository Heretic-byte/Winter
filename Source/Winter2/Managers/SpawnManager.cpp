// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnManager.h"

#include "Components/CapsuleComponent.h"
#include "Winter2/MyLib.h"
#include "Winter2/Winter2Character.h"
#include "Winter2/Actor/Pawn/Character/BaseCharacter.h"


USpawnManager::USpawnManager()
{
	//SpawnData.m_EntityParentTable->RowStruct->IsChildOf(FNpcUnitEntityRow::StaticStruct())
}
//
// void USpawnManager::SetSpawnActors(const UNPCPaletteDataAsset* npcAssets)
// {
// 	if(!npcAssets||npcAssets->m_ArySpawnDatas.Num()<1)
// 	{
// 		return;
// 	}
// 	//처음에는 한번에 스폰시켜야함
// 	//계속해서 스폰시켜야함
// 	m_AryNpcActors.Reset();
//
// 	for(const FNPCSpawnData& SpawnDataEle : npcAssets->m_ArySpawnDatas)
// 	{
// 		SpawnNpcActor(SpawnDataEle,npcAssets);	
// 	}
// }

void USpawnManager::SpawnPlayer(const FVector& loc, const FRotator& rot)
{
	//50
	float Diff =UMyLib::GetPlayer()->GetCapsuleComponent()->GetScaledCapsuleHalfHeight() - 50;

	FVector LocNew = loc;

	LocNew.Z+=Diff;
	
	UMyLib::GetPlayer()->SetActorLocation(LocNew,true);
	
	UMyLib::GetPlayer()->SetActorRotation(rot);
}

void USpawnManager::RegisterActor(ABaseCharacter* pawn)
{
	
}

//void USpawnManager::OnMonsterDead(const AMonsterPawn* monster)
//{
//	m_OnMonsterDead.Broadcast(monster->m_PawnName);
//
//	UMyGameInstance::Get->m_CurrencyManager->AddGold(monster->GetRewardGold());
//	
//	UMyGameInstance::Get->m_RewardManager->RequestMonsterReward();
//}

//ABaseCharacter* USpawnManager::SpawnNpcActor(const FNPCSpawnData& SpawnData,const UNPCPaletteDataAsset* dataAsset)
//{
//	FActorSpawnParameters Param;
//
//	Param.bNoFail = true;
//
//	Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
//
//	AMonsterPawn* NpcActor = UMyLib::GetUWorld()->SpawnActor<AMonsterPawn>(AMonsterPawn::StaticClass(), SpawnData.m_SpawnPosition, SpawnData.m_SpawnRotation, Param);
//	
//	const FNpcUnitEntityRow* EntityRow = UUnitEntityData::GetNpcUnitTable->FindRow<FNpcUnitEntityRow>(SpawnData.m_IDEntity, "");
//
//	if(EntityRow)
//	{
//		NpcActor->SetEntity(*EntityRow);
//
//		NpcActor->SetReviveTime(dataAsset->m_fSpawnMinTime,dataAsset->m_fSpawnMaxTime);
//	}
//
//	m_AryNpcActors.Add(NpcActor);
//	
//	return NpcActor;
//}

ABaseCharacter* USpawnManager::GetNearNpc(FVector callerLoc, float range)
{
	float MAX_Dist = MAX_flt;

	range = range * range;
	
	ABaseCharacter* NearPawn = nullptr;

	ABaseCharacter* PlayerPawn = UMyLib::GetPlayer();

	FNavLocation StartPoint;

	UNavigationSystemV1* NavSys = UMyLib::GetNavSys();

	NavSys->ProjectPointToNavigation(callerLoc, StartPoint);

	for(ABaseCharacter* Pawn : m_AryNpcActors)
	{
		if(!Pawn || !Pawn->IsAlive() || Pawn->IsHidden())
		{
			continue;
		}

		float Length = MAX_flt;

		FNavLocation EndPoint;

		NavSys->ProjectPointToNavigation(Pawn->GetActorLocation(), EndPoint);

		if(!PlayerPawn->LineOfSightTo(Pawn))
		{
			UMyLib::GetNavSys()->GetPathLength(GetWorld(),StartPoint,EndPoint,Length);
			
			Length = Length*Length;
		}
		else
		{
			Length = FVector::DistSquared2D(StartPoint,EndPoint);
		}

		if (range > 0 && range < Length)
		{
			continue;
		}

		if(MAX_Dist>Length)
		{
			NearPawn=Pawn;
			
			MAX_Dist=Length;
		}
	}

	return NearPawn;
}

void USpawnManager::HideActors()
{
	for(auto* Pawn : m_AryNpcActors)
	{
		if(Pawn)
		{
			Pawn->SetActive(false);
		}
	}
}

void USpawnManager::ShowActors()
{
	for(ABaseCharacter* Pawn : m_AryNpcActors)
	{
		if(Pawn)
		{
			Pawn->SetActive(true);
		}
	}
}

