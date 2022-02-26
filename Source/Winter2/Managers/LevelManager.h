// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LevelManager.generated.h"

/**
 * 
 */
UCLASS()
class WINTER2_API ULevelManager : public UObject
{
	GENERATED_BODY()
	
public:
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnLevelMoveComplete,FText);

	FOnLevelMoveComplete m_OnLvelMoveComp;

protected:
	FName m_MapID;
public:
	void OpenMyLevel(FName mapLevelName);

	void OnOpenWorldLevelComplete();
	
	bool IsGameStart();
	
	void HideCurrentLevel();

	void ShowCurrentLevel();

	const FName& GetMapID() const;
};
