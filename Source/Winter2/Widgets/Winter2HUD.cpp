// Copyright Epic Games, Inc. All Rights Reserved.

#include "Winter2HUD.h"
#include "Engine/Canvas.h"
#include "Engine/Texture2D.h"
#include "TextureResource.h"
#include "CanvasItem.h"
#include "UObject/ConstructorHelpers.h"
#include "Winter2/MyLib.h"
#include "Winter2/Actor/Pawn/Character/Winter2Character.h"

AWinter2HUD::AWinter2HUD()
{
	// Set the crosshair texture
	static ConstructorHelpers::FObjectFinder<UTexture2D> CrosshairTexObj(TEXT("/Game/FirstPerson/Textures/FirstPersonCrosshair"));
	CrosshairTex = CrosshairTexObj.Object;
}


void AWinter2HUD::DrawHUD()
{
	Super::DrawHUD();

	// Draw very simple crosshair

	// find center of the Canvas
	const FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);

	// offset by half the texture's dimensions so that the center of the texture aligns with the center of the Canvas
	const FVector2D CrosshairDrawPosition( (Center.X),
										   (Center.Y + 20.0f));


	FLinearColor DrawColor = FLinearColor::White;

	if(UMyLib::GetPlayer())
	{
		if(UMyLib::GetPlayer()->HasTarget())
		{
			DrawColor = FLinearColor(50,50,50,50);
		}
	}
	
	FCanvasTileItem TileItem( CrosshairDrawPosition, CrosshairTex->Resource, DrawColor);
	TileItem.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem( TileItem );
}

void AWinter2HUD::BeginPlay()
{
	Super::BeginPlay();
	
	//m_Canvas = CreateWidget<UMainCanvas>(GetWorld(), m_ClassWidget);
	//
	//if(m_Canvas)
	//{
	//	m_Canvas->AddToViewport();
	//}
}
