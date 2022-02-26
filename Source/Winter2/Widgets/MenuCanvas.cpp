#include "MenuCanvas.h"
#include "Kismet/GameplayStatics.h"
#include "Winter2/MyLib.h"
#include "Winter2/Managers/MyGameInstance.h"

void UMenuCanvas::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	m_BtnBackToTitleGame->OnClicked.AddDynamic(this, &UMenuCanvas::OnBackTitle);

	m_BtnRestartNewGame->OnClicked.AddDynamic(this, &UMenuCanvas::OnRestartNewGame);

	m_BtnExitGame->OnClicked.AddDynamic(this, &UMenuCanvas::OnExitGame);

	m_BtnClose->OnClicked.AddDynamic(this, &UMenuCanvas::OnClose);

	SetVisibility(ESlateVisibility::Collapsed);

	m_ImgWinBG->SetVisibility(ESlateVisibility::Collapsed);
}

void UMenuCanvas::OpenAsPause()
{
	if(IsVisible())
	{
		OnClose();
		return;
	}
	UGameplayStatics::SetGamePaused(GetWorld(),true);
	SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	UMyLib::GetPlayerCon()->SetInputMode(FInputModeGameAndUI());
	UMyLib::GetPlayerCon()->bShowMouseCursor = true;

	m_TextMenu->SetText(FText::FromString(TEXT("일시정지")));
}

void UMenuCanvas::OpenAsWin()
{
	if(IsVisible())
	{
		OnClose();
		return;
	}
	UGameplayStatics::SetGamePaused(GetWorld(),true);
	SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	UMyLib::GetPlayerCon()->SetInputMode(FInputModeGameAndUI());
	UMyLib::GetPlayerCon()->bShowMouseCursor = true;

	m_TextMenu->SetText(FText::FromString(TEXT("생존 성공!")));

	m_ImgWinBG->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}
//SoundWave'/Game/Audio/BGM_End.BGM_End'
void UMenuCanvas::OpenAsLose()
{
	if(IsVisible())
	{
		OnClose();
		return;
	}
	UGameplayStatics::SetGamePaused(GetWorld(),true);
	SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	UMyLib::GetPlayerCon()->SetInputMode(FInputModeGameAndUI());
	UMyLib::GetPlayerCon()->bShowMouseCursor = true;

	m_TextMenu->SetText(FText::FromString(TEXT("생존 실패!")));
}

void UMenuCanvas::OnBackTitle()
{
	UMyGameInstance::Get->OpenMap(TEXT("InitLevel"));
}

void UMenuCanvas::OnRestartNewGame()
{
	UMyGameInstance::Get->StartGame();
}

void UMenuCanvas::OnExitGame()
{
	UMyGameInstance::Get->ExitGame();
}

void UMenuCanvas::OnClose()
{
	UGameplayStatics::SetGamePaused(GetWorld(),false);
	SetVisibility(ESlateVisibility::Collapsed);
	UMyLib::GetPlayerCon()->SetInputMode(FInputModeGameOnly());
	UMyLib::GetPlayerCon()->bShowMouseCursor = false;
}

