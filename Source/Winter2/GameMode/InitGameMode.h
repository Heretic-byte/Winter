// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "Winter2/Widgets/TitleCanvas.h"
#include "InitGameMode.generated.h"

/**
 * 
 */
UCLASS()
class WINTER2_API AInitGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AInitGameMode();

protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<UTitleCanvas> m_ClassWidget;
	UPROPERTY()
	UTitleCanvas* m_Canvas;

protected:
	virtual void BeginPlay() override;
};
