// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LevelManager.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class WINTER2_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

protected:
	bool m_bIsPlayerWin;
public:
	static UMyGameInstance* Get;

public:
	UPROPERTY()
	ULevelManager* m_ZoneMoveManager;
	
public:
	virtual void Init() override;

	virtual void LoadComplete(const float LoadTime, const FString& MapName) override;
	
	void StartGame();

	void OpenMap(FName mapName);

	void ExitGame();
	
	void WinGame();

	bool IsPlayerWin();
};
