// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterStat/MyCharacterStatComponent.h"
#include "MyGameSingleton.h"

UMyCharacterStatComponent::UMyCharacterStatComponent()
{
	CurrentLevel = 1;
}

void UMyCharacterStatComponent::BeginPlay()
{
	Super::BeginPlay();

	SetLevelStat(CurrentLevel);
	SetHP(BaseStat.MaxHP);
}

void UMyCharacterStatComponent::SetLevelStat(int32 InNewLevel)
{
	CurrentLevel = FMath::Clamp(InNewLevel, 1, UMyGameSingleton::Get().CharacterMaxLevel);
	BaseStat = UMyGameSingleton::Get().GetCharacterStat(CurrentLevel);
	check(BaseStat.MaxHP > 0.0f);
}

float UMyCharacterStatComponent::ApplyDamage(float InDamage)
{
	const float PrevHP = CurrentHP;
	const float ActualDamage = FMath::Clamp<float>(InDamage, 0, InDamage);

	SetHP(PrevHP - ActualDamage);
	if (CurrentHP <= KINDA_SMALL_NUMBER)
	{
		OnHPZero.Broadcast();
	}

	return ActualDamage;
}

void UMyCharacterStatComponent::SetHP(float NewHP)
{
	CurrentHP = FMath::Clamp<float>(NewHP, 0.0f, BaseStat.MaxHP);

	OnHPChanged.Broadcast(CurrentHP);
}

