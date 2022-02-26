// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SpawnManager.generated.h"

class ABaseCharacter;
/**
 * 
 */
UCLASS()
class WINTER2_API USpawnManager : public UObject
{
	GENERATED_BODY()
	
public:
	USpawnManager();

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnMonsterDead,FText);

	FOnMonsterDead m_OnMonsterDead;
	
protected:
	UPROPERTY()
	TArray<ABaseCharacter*> m_AryNpcActors;

protected:
	//ABaseCharacter* SpawnNpcActor(const FNPCSpawnData& SpawnData,const UNPCPaletteDataAsset* dataAsset);

	//AActor* SpawnPropActor(const FNPCSpawnData& SpawnData,const UNPCPaletteDataAsset* dataAsset);
	
public:
	ABaseCharacter* GetNearNpc(FVector callerLoc, float range = 0);

public:
	void HideActors();
	
	void ShowActors();
	
	//void SetSpawnActors(const UNPCPaletteDataAsset* npcAssets);
	
	void SpawnPlayer(const FVector& loc, const FRotator& rot);
	
	void RegisterActor(ABaseCharacter* pawn);

	//void OnMonsterDead(const AMonsterPawn* monster);

	//ASummonUnitPawn* SummonUnit(FName unit_id ,FVector loc,float lifetime);
};
