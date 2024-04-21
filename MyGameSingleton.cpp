// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameSingleton.h"

DEFINE_LOG_CATEGORY(LogABGameSingleton);


UMyGameSingleton::UMyGameSingleton()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DataTableRef(TEXT("/Script/Engine.DataTable'/Game/MyContents/DataTable/MyDT_Stat.MyDT_Stat'"));
	if (nullptr != DataTableRef.Object)
	{
		const UDataTable* DataTable = DataTableRef.Object;
		check(DataTable->GetRowMap().Num() > 0);

		TArray<uint8*> ValueArray;
		DataTable->GetRowMap().GenerateValueArray(ValueArray);
		Algo::Transform(ValueArray, CharacterStatTable,
			[](uint8* Value)
			{
				return *reinterpret_cast<FMyStatData*>(Value);
			}
		);
	}

	CharacterMaxLevel = CharacterStatTable.Num();
	ensure(CharacterMaxLevel > 0);
}

UMyGameSingleton& UMyGameSingleton::Get()
{
	UMyGameSingleton* Singleton = CastChecked< UMyGameSingleton>(GEngine->GameSingleton);
	if (Singleton)
	{
		return *Singleton;
	}

	UE_LOG(LogABGameSingleton, Error, TEXT("Invalid Game Singleton"));
	return *NewObject<UMyGameSingleton>();
}
