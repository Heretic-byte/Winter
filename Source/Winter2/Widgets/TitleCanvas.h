// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "TitleCanvas.generated.h"

/**
 * 
 */
UCLASS()
class WINTER2_API UTitleCanvas : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget,AllowPrivateAccess = "true"))
	UButton* m_BtnStartGame;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget,AllowPrivateAccess = "true"))
	UButton* m_BtnExitGame;

protected:
	virtual void NativeOnInitialized() override;
	
public:
	UFUNCTION()
	void OnStartGame();
	UFUNCTION()
	void OnExitGame();
};
