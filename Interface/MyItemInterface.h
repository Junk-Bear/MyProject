// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MyItemInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UMyItemInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MYPROJECT_API IMyItemInterface
{
	GENERATED_BODY()

public:
	virtual void TakeItem(class UMyItemDataAsset* InItemData) = 0;
};
