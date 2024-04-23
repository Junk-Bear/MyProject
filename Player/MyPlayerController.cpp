// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MyPlayerController.h"
#include "UI/MyHUDWidget.h"

AMyPlayerController::AMyPlayerController()
{
	static ConstructorHelpers::FClassFinder<UMyHUDWidget> MyHUDWidgetRef(TEXT("/Game/MyContents/UI/MyWBP_HUD.MyWBP_HUD_C"));
	if (MyHUDWidgetRef.Class)
	{
		HUDWidgetClass = MyHUDWidgetRef.Class;
	}
}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly GameOnlyInputMode;
	SetInputMode(GameOnlyInputMode);

	HUDWidget = CreateWidget<UMyHUDWidget>(this, HUDWidgetClass);
	if (HUDWidget)
	{
		HUDWidget->AddToViewport();
	}
}
