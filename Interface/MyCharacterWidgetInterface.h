// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MyCharacterWidgetInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UMyCharacterWidgetInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MYPROJECT_API IMyCharacterWidgetInterface
{
	GENERATED_BODY()

public:
	virtual void SetupCharacterWidget(class UMyUserWidget* InUserWidget) = 0;
};
