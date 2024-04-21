// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/MyCharacterBase.h"
#include "Engine/StreamableManager.h"
#include "MyEnemyNPC.generated.h"

/**
 * 
 */
UCLASS(config = ArenaBattle)
class MYPROJECT_API AMyEnemyNPC : public AMyCharacterBase
{
	GENERATED_BODY()
	
public:
	AMyEnemyNPC();

protected:
	virtual void PostInitializeComponents() override;

protected:
	void SetDead() override;
	void NPCMeshLoadCompleted();

	UPROPERTY(config)
	TArray<FSoftObjectPath> NPCMeshes;

	TSharedPtr<FStreamableHandle> NPCMeshHandle;
};
