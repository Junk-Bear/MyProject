// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MyPlayerController.h"

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly GameOnlyInputMode;
	SetInputMode(GameOnlyInputMode);
}
