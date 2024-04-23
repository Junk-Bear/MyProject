// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/MyItemDataAsset.h"
#include "GameData/MyStatData.h"
#include "MyScrollItemDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UMyScrollItemDataAsset : public UMyItemDataAsset
{
	GENERATED_BODY()
	
public:
	UMyScrollItemDataAsset();

	FPrimaryAssetId GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId("MyItemDataAsset", GetFName());
	}

public:
	UPROPERTY(EditAnywhere, Category = stat)
	FMyStatData BaseStat;
};
