// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Winter2GameMode.generated.h"

class AMyPlayerController;
UCLASS(minimalapi)
class AWinter2GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AWinter2GameMode();

protected:
	float m_fTimePassed;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,DisplayName="Game Win, Sec, 600.f = 10 min")
	float m_fGameWinTime;

protected:
	virtual void Tick(float DeltaSeconds) override;

public:
	UFUNCTION(BlueprintCallable)
	float GetTimePassed();
	UFUNCTION(BlueprintCallable)
	float GetWinMaxTime();
	UFUNCTION(BlueprintCallable)
	float GetTimePercentOne();
	UFUNCTION(BlueprintCallable)
	FString UpdateTimePassed();
};



