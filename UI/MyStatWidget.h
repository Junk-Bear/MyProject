// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameData/MyStatData.h"
#include "MyStatWidget.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UMyStatWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	void UpdateStat(const FMyStatData& BaseStat, const FMyStatData& ModifierStat);

private:
	UPROPERTY()
	TMap<FName, class UTextBlock*> BaseLookup;

	UPROPERTY()
	TMap<FName, class UTextBlock*> ModifierLookup;
};
