// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MyControlDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UMyControlDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category = MoveSpeed)
	float WalkSpeed;
	UPROPERTY(EditAnywhere, Category = MoveSpeed)
	float RunSpeed;
	
};
