// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameData/MyStatData.h"
#include "MyGameSingleton.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogABGameSingleton, Error, All);
/**
 * 
 */
UCLASS()
class MYPROJECT_API UMyGameSingleton : public UObject
{
	GENERATED_BODY()

public:
	UMyGameSingleton();
	static UMyGameSingleton& Get();

	// Character Stat Data Section
public:
	FORCEINLINE FMyStatData GetCharacterStat(int32 InLevel) const { return CharacterStatTable.IsValidIndex(InLevel - 1) ? CharacterStatTable[InLevel - 1] : FMyStatData(); }

	UPROPERTY()
	int32 CharacterMaxLevel;

private:
	TArray<FMyStatData> CharacterStatTable;
};
