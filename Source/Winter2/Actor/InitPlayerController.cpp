// Fill out your copyright notice in the Description page of Project Settings.


#include "InitPlayerController.h"

#include "Winter2/MyLib.h"
#include "Winter2/Winter2.h"
#include "Winter2/Widgets/MenuCanvas.h"

AInitPlayerController::AInitPlayerController()
{
	//CheatClass = UMyCheatManager::StaticClass();
	
	bShowMouseCursor = true;
}

void AInitPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	//InputComponent->BindAction(TEXT("Esc"), EInputEvent::IE_Pressed, this, &AInitPlayerController::OnPressEsc);
}

void AInitPlayerController::OnPressEsc()
{
	//PRINTF("AMyPlayerController::OnPressEsc");
	//UMyLib::GetMenuCanvas()->OpenAsPause();
}
