// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/MyAttackAnimationInterface.h"
#include "Interface/MyCharacterWidgetInterface.h"
#include "interface/MyItemInterface.h"
#include "MyCharacterBase.generated.h"


DECLARE_LOG_CATEGORY_EXTERN(LogMyCharacter, Log, All);

DECLARE_DELEGATE_OneParam(FOnTakeItemDelegate, class UMyItemDataAsset* /*InItemData*/);
USTRUCT(BlueprintType)
struct FTakeItemDelegateWrapper
{
	GENERATED_BODY()
	FTakeItemDelegateWrapper() {}
	FTakeItemDelegateWrapper(const FOnTakeItemDelegate& InItemDelegate) : ItemDelegate(InItemDelegate) {}
	FOnTakeItemDelegate ItemDelegate;
};


UCLASS()
class MYPROJECT_API AMyCharacterBase : public ACharacter, public IMyAttackAnimationInterface, public IMyCharacterWidgetInterface, public IMyItemInterface
{
	GENERATED_BODY()

public:
	AMyCharacterBase();

	virtual void PostInitializeComponents() override;

protected:
	virtual void SetCharacterControlData(const class UMyControlDataAsset* InDataAsset);

	UPROPERTY(EditAnywhere, Category = CharactorControl, Meta=(AllowPrivateAccess = "true"))
	TObjectPtr<class UMyControlDataAsset> ControlDataAsset;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<class UAnimMontage> ComboActionMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UMyComboDataAsset> ComboActionData;

	void ProcessComboCommand();

	void ComboActionBegin();
	void ComboActionEnd(class UAnimMontage* TargetMontage, bool IsProperlyEnded);
	void SetComboCheckTimer();
	void ComboCheck();

	int32 CurrentCombo = 0;
	FTimerHandle ComboTimerHandle;
	bool HasNextComboCommand = false;

protected:
	virtual void AttackHitCheck() override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stat, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAnimMontage> DeadMontage;

	virtual void SetDead();
	void PlayDeadAnimation();

	float DeadEventDelayTime = 5.0f;


protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UMyCharacterStatComponent> Stat;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Widget, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UWidgetComponent> HPBar;

	virtual void SetupCharacterWidget(class UMyUserWidget* InUserWidget) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Equipment, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USkeletalMeshComponent> Weapon;

	UPROPERTY()
	TArray<FTakeItemDelegateWrapper> TakeItemActions;

	virtual void TakeItem(class UMyItemDataAsset* InItemData) override;
	virtual void DrinkPotion(class UMyItemDataAsset* InItemData);
	virtual void EquipWeapon(class UMyItemDataAsset* InItemData);
	virtual void ReadScroll(class UMyItemDataAsset* InItemData);
};
