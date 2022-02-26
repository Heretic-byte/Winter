// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "MenuCanvas.h"
#include "GameFramework/HUD.h"
#include "Winter2HUD.generated.h"

UCLASS()
class AWinter2HUD : public AHUD
{
	GENERATED_BODY()

public:
	AWinter2HUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	class UTexture2D* CrosshairTex;
	UPROPERTY()
	TSubclassOf<UMenuCanvas> m_ClassMenu;
	UPROPERTY()
	UMenuCanvas* m_Canvas;

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	void OpenAsPause();
	UFUNCTION(BlueprintCallable)
	void OpenAsWin();
	UFUNCTION(BlueprintCallable)
	void OpenAsLose();

	UMenuCanvas* GetCanvas()
	{
		return m_Canvas;
	}
};

