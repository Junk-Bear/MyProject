// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterStat/MyCharacterStatComponent.h"

UMyCharacterStatComponent::UMyCharacterStatComponent()
{
	MaxHP = 200.f;
	CurrentHP = MaxHP;
}

void UMyCharacterStatComponent::BeginPlay()
{
	Super::BeginPlay();

	SetHP(MaxHP);
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
	CurrentHP = FMath::Clamp<float>(NewHP, 0.f, MaxHP);

	OnHPChanged.Broadcast(CurrentHP);
}

