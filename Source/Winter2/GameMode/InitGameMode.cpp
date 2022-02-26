// Fill out your copyright notice in the Description page of Project Settings.


#include "InitGameMode.h"

#include "Blueprint/UserWidget.h"
#include "Winter2/Actor/InitPlayerController.h"
#include "Winter2/Actor/MyPlayerController.h"
#include "Winter2/Widgets/TitleCanvas.h"

AInitGameMode::AInitGameMode()
{
	static ConstructorHelpers::FClassFinder<UTitleCanvas> FoundC(TEXT("WidgetBlueprint'/Game/BP/Widgets/WB_Title.WB_Title_C'"));
	m_ClassWidget =  FoundC.Class;
	//WidgetBlueprint'/Game/BP/Widgets/WB_Title.WB_Title'
	HUDClass = nullptr;
	DefaultPawnClass=nullptr;
	PlayerControllerClass = AInitPlayerController::StaticClass();
}

void AInitGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	m_Canvas = CreateWidget<UTitleCanvas>(GetWorld(), m_ClassWidget);

	if(m_Canvas)
	{
		m_Canvas->AddToViewport();
	}
}
