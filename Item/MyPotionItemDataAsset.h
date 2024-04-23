// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/MyItemDataAsset.h"
#include "MyPotionItemDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UMyPotionItemDataAsset : public UMyItemDataAsset
{
	GENERATED_BODY()

public:
	UMyPotionItemDataAsset();

	FPrimaryAssetId GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId("ABItemData", GetFName());
	}

public:
	UPROPERTY(EditAnywhere, Category = Hp)
	float HealAmount;
};
