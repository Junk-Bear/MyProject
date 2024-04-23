// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameData/MyStatData.h"
#include "MyCharacterStatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHpZeroDelegate);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHpChangedDelegate, float /*CurrentHp*/);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnStatChangedDelegate, const FMyStatData& /*BaseStat*/, const FMyStatData& /*ModifierStat*/);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT_API UMyCharacterStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UMyCharacterStatComponent();

protected:
	virtual void InitializeComponent() override;

public:
	FOnHpZeroDelegate OnHPZero;
	FOnHpChangedDelegate OnHPChanged;
	FOnStatChangedDelegate OnStatChanged;

	void SetLevelStat(int32 InNewLevel);
	FORCEINLINE float GetCurrentLevel() const { return CurrentLevel; }
	FORCEINLINE FMyStatData GetTotalStat() const { return BaseStat + ModifierStat; }
	FORCEINLINE float GetCurrentHP() const { return CurrentHP; }
	FORCEINLINE float GetAttackRadius() const { return AttackRadius; }

	FORCEINLINE const FMyStatData& GetBaseStat() const { return BaseStat; }
	FORCEINLINE const FMyStatData& GetModifierStat() const { return ModifierStat; }
	FORCEINLINE void SetBaseStat(const FMyStatData& InBaseStat) { BaseStat = InBaseStat; OnStatChanged.Broadcast(GetBaseStat(), GetModifierStat()); }
	FORCEINLINE void SetModifierStat(const FMyStatData& InModifierStat) { ModifierStat = InModifierStat; OnStatChanged.Broadcast(GetBaseStat(), GetModifierStat()); }
	float ApplyDamage(float InDamage);

protected:
	void SetHP(float NewHP);

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat)
	float CurrentHP;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat)
	float CurrentLevel;

	UPROPERTY(VisibleInstanceOnly, Category = Stat, Meta =(AllowPrivateAccess = "true"))
	float AttackRadius;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = "true"))
	FMyStatData BaseStat;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = "true"))
	FMyStatData ModifierStat;
};
