// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "Winter2/MyLib.h"
#include "Winter2/Winter2.h"
#include "Winter2/Widgets/MenuCanvas.h"
//InputComponent->BindAction("Exit", EInputEvent::IE_Pressed, this, &ADiabloPlayerController::ExitGame);
AMyPlayerController::AMyPlayerController()
{
	//CheatClass = UMyCheatManager::StaticClass();
	bShowMouseCursor = false;
}

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction(TEXT("Esc"), EInputEvent::IE_Pressed, this, &AMyPlayerController::OnPressEsc);
}

void AMyPlayerController::OnPressEsc()
{
	PRINTF("AMyPlayerController::OnPressEsc");
	UMyLib::GetMenuCanvas()->OpenAsPause();
}
