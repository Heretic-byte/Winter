// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "MenuCanvas.generated.h"

/**
 * 
 */
UCLASS()
class WINTER2_API UMenuCanvas : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget,AllowPrivateAccess = "true"))
	UTextBlock* m_TextMenu;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget,AllowPrivateAccess = "true"))
	UButton* m_BtnBackToTitleGame;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget,AllowPrivateAccess = "true"))
	UButton* m_BtnRestartNewGame;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget,AllowPrivateAccess = "true"))
	UButton* m_BtnExitGame;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget,AllowPrivateAccess = "true"))
	UButton* m_BtnClose;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget,AllowPrivateAccess = "true"))
	UImage* m_ImgWinBG;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget,AllowPrivateAccess = "true"))
	UCanvasPanel* m_CanvasTutorial; 
	
protected:
	virtual void NativeOnInitialized() override;

	
public:
	UFUNCTION(BlueprintCallable)
	void OpenAsPause();
	UFUNCTION(BlueprintCallable)
	void OpenAsWin();
	UFUNCTION(BlueprintCallable)
	void OpenAsLose();
	
public:
	UFUNCTION(BlueprintCallable)
	void OnBackTitle();
	UFUNCTION(BlueprintCallable)
	void OnRestartNewGame();
	UFUNCTION(BlueprintCallable)
	void OnExitGame();
	UFUNCTION(BlueprintCallable)
	void OnClose();
};


