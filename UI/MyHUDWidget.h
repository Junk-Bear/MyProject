// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameData/MyStatData.h"
#include "MyHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UMyHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UMyHUDWidget(const FObjectInitializer& ObjectInitializer);

public:
	void UpdateStat(const FMyStatData& BaseStat, const FMyStatData& ModifierStat);
	void UpdateHPBar(float NewCurrentHP);

protected:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY()
	TObjectPtr<class UMyHPBarWidget> HPBar;

	UPROPERTY()
	TObjectPtr<class UMyStatWidget> CharacterStat;
};
