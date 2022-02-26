// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InitPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class WINTER2_API AInitPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AInitPlayerController();

protected:
	virtual void SetupInputComponent() override;

protected:
	void OnPressEsc();
};
