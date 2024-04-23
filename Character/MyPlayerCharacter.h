// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/MyCharacterBase.h"
#include "InputActionValue.h"
#include "Interface/MyCharacterHUDInterface.h"
#include "MyPlayerCharacter.generated.h"

/**
 *
 */
UCLASS()
class MYPROJECT_API AMyPlayerCharacter : public AMyCharacterBase, public IMyCharacterHUDInterface
{
	GENERATED_BODY()

public:
	AMyPlayerCharacter();

protected:
	virtual void BeginPlay() override;
	virtual void SetDead() override;

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Camera Section
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> FollowCamera;

	// Input Section
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> RunAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> DefalutAttackAction;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

	void TriggerRun();
	void ReleaseRun();

	void DefaultAttack();

	virtual void SetCharacterControlData(const class UMyControlDataAsset* InDataAsset) override;

protected:
	virtual void SetupHUDWidget(class UMyHUDWidget* InHUDWidget) override;
};
