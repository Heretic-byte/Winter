// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LevelManager.h"
#include "PlayerStatusManager.h"
#include "SpawnManager.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class WINTER2_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	static UMyGameInstance* Get;

public:
	UPROPERTY()
	ULevelManager* m_ZoneMoveManager;
	UPROPERTY()
	USpawnManager* m_SpawnManager;
	UPROPERTY()
	UPlayerStatusManager* m_PlayerStatManager;
	
public:
	virtual void Init() override;

	virtual void LoadComplete(const float LoadTime, const FString& MapName) override;
	
	void StartGame();

	void ExitGame();
};
