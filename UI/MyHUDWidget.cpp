// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MyHUDWidget.h"
#include "MyHpBarWidget.h"
#include "GameData/MyStatData.h"
#include "Interface/MyCharacterHUDInterface.h"
#include "UI/MyStatWidget.h"

UMyHUDWidget::UMyHUDWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UMyHUDWidget::UpdateStat(const FMyStatData& BaseStat, const FMyStatData& ModifierStat)
{
	FMyStatData TotalStat = BaseStat + ModifierStat;
	HPBar->UpdateStat(BaseStat, ModifierStat);

	CharacterStat->UpdateStat(BaseStat, ModifierStat);
}

void UMyHUDWidget::UpdateHPBar(float NewCurrentHP)
{
	HPBar->UpdateHPBar(NewCurrentHP);
}

void UMyHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();


	HPBar = Cast<UMyHPBarWidget>(GetWidgetFromName(TEXT("WidgetHPBar")));
	ensure(HPBar);

	CharacterStat = Cast<UMyStatWidget>(GetWidgetFromName(TEXT("WidgetStatTextBox")));
	ensure(CharacterStat);

	IMyCharacterHUDInterface* HUDPawn = Cast<IMyCharacterHUDInterface>(GetOwningPlayerPawn());
	if (HUDPawn)
	{
		HUDPawn->SetupHUDWidget(this);
	}
}
