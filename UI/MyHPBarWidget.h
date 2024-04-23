// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyUserWidget.h"
#include  "GameData/MyStatData.h"
#include "MyHPBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UMyHPBarWidget : public UMyUserWidget
{
	GENERATED_BODY()

public:
	UMyHPBarWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

public:
	void UpdateStat(const FMyStatData& BaseStat, const FMyStatData& ModifierStat);
	void UpdateHPBar(float NewCurrentHP);
	FString GetHPStatText();

protected:
	UPROPERTY()
	TObjectPtr<class UProgressBar> HPProgressBar;

	UPROPERTY()
	TObjectPtr<class UTextBlock> HPStat;

	UPROPERTY()
	float CurrentHP;

	UPROPERTY()
	float MaxHP;
};
