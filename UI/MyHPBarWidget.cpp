// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MyHPBarWidget.h"
#include "Components/ProgressBar.h"
#include "Interface/MyCharacterWidgetInterface.h"

UMyHPBarWidget::UMyHPBarWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	MaxHP = -1.0f;
}

void UMyHPBarWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HPProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PB_HPBar")));
	ensure(HPProgressBar);

	IMyCharacterWidgetInterface* CharacterWidget = Cast<IMyCharacterWidgetInterface>(OwningActor);
	if (CharacterWidget)
	{
		CharacterWidget->SetupCharacterWidget(this);
	}
}

void UMyHPBarWidget::UpdateHPBar(float NewCurrentHp)
{
	ensure(MaxHP > 0.0f);
	if (HPProgressBar)
	{
		HPProgressBar->SetPercent(NewCurrentHp / MaxHP);
	}
}
