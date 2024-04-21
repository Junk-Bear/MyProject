// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/MyItemDataAsset.h"
#include "MyWeaponItemDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UMyWeaponItemDataAsset : public UMyItemDataAsset
{
	GENERATED_BODY()

public:
	FPrimaryAssetId GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId("MyItemDataAsset", GetFName());
	}

public:
	UPROPERTY(EditAnywhere, Category = Weapon)
	TSoftObjectPtr<USkeletalMesh> WeaponMesh;
	
};
