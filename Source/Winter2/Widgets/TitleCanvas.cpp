// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleCanvas.h"

#include "Winter2/Winter2.h"
#include "Winter2/Managers/MyGameInstance.h"

void UTitleCanvas::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	m_BtnStartGame->OnClicked.AddDynamic(this,&UTitleCanvas::OnStartGame);
	
	m_BtnExitGame->OnClicked.AddDynamic(this,&UTitleCanvas::OnExitGame);
}

void UTitleCanvas::OnStartGame()
{
	PRINTF("OnStartGame");
	UMyGameInstance::Get->StartGame();
}

void UTitleCanvas::OnExitGame()
{
	PRINTF("OnExitGame");
	UMyGameInstance::Get->ExitGame();
}
