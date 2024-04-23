// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MyHPBarWidget.h"
#include "Components/ProgressBar.h"
#include "Interface/MyCharacterWidgetInterface.h"
#include "Components/TextBlock.h"

UMyHPBarWidget::UMyHPBarWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	MaxHP = -1.0f;
}

void UMyHPBarWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HPProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PB_HPBar")));
	ensure(HPProgressBar);

	HPStat = Cast<UTextBlock>(GetWidgetFromName(TEXT("Txt_HPStat")));
	ensure(HPStat);

	IMyCharacterWidgetInterface* CharacterWidget = Cast<IMyCharacterWidgetInterface>(OwningActor);
	if (CharacterWidget)
	{
		CharacterWidget->SetupCharacterWidget(this);
	}
}

void UMyHPBarWidget::UpdateStat(const FMyStatData& BaseStat, const FMyStatData& ModifierStat)
{
	MaxHP = (BaseStat + ModifierStat).MaxHP;

	if (HPProgressBar)
	{
		HPProgressBar->SetPercent(CurrentHP / MaxHP);
	}

	if (HPStat)
	{
		HPStat->SetText(FText::FromString(GetHPStatText()));
	}
}

void UMyHPBarWidget::UpdateHPBar(float NewCurrentHP)
{
	CurrentHP = NewCurrentHP;

	ensure(MaxHP > 0.0f);
	if (HPProgressBar)
	{
		HPProgressBar->SetPercent(CurrentHP / MaxHP);
	}

	if (HPStat)
	{
		HPStat->SetText(FText::FromString(GetHPStatText()));
	}
}

FString UMyHPBarWidget::GetHPStatText()
{
	return FString::Printf(TEXT("%.0f/%0.f"), CurrentHP, MaxHP);
}
