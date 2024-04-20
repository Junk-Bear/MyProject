// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyUserWidget.h"
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
	FORCEINLINE void SetMaxHP(float NewMaxHP) { MaxHP = NewMaxHP; }
	void UpdateHPBar(float NewCurrentHP);

protected:
	UPROPERTY()
	TObjectPtr<class UProgressBar> HPProgressBar;

	UPROPERTY()
	float MaxHP;
};
