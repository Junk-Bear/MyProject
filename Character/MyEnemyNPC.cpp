// Fill out your copyright notice in the Description page of Project Settings.


#include "MyEnemyNPC.h"
#include "Engine/AssetManager.h"
#include "AI/MyAIController.h"
#include "CharacterStat/MyCharacterStatComponent.h"

AMyEnemyNPC::AMyEnemyNPC()
{
	GetMesh()->SetHiddenInGame(true);

	AIControllerClass = AMyAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AMyEnemyNPC::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	ensure(NPCMeshes.Num() > 0);
	int32 RandIndex = FMath::RandRange(0, NPCMeshes.Num() - 1);
	NPCMeshHandle = UAssetManager::Get().GetStreamableManager().RequestAsyncLoad(NPCMeshes[RandIndex], FStreamableDelegate::CreateUObject(this, &AMyEnemyNPC::NPCMeshLoadCompleted));
}

void AMyEnemyNPC::SetDead()
{
	Super::SetDead();

	FTimerHandle DeadTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(DeadTimerHandle, FTimerDelegate::CreateLambda(
		[&]()
		{
			Destroy();
		}
	), DeadEventDelayTime, false);
}

void AMyEnemyNPC::NPCMeshLoadCompleted()
{
	if (NPCMeshHandle.IsValid())
	{
		USkeletalMesh* NPCMesh = Cast<USkeletalMesh>(NPCMeshHandle->GetLoadedAsset());
		if (NPCMesh)
		{
			GetMesh()->SetSkeletalMesh(NPCMesh);
			GetMesh()->SetHiddenInGame(false);
		}
	}

	NPCMeshHandle->ReleaseHandle();
}

float AMyEnemyNPC::GetAIPatrolRadius()
{
	return 800.0f;
}

float AMyEnemyNPC::GetAIDetectRange()
{
	return 400.0f;
}

float AMyEnemyNPC::GetAIAttackRange()
{
	return Stat->GetTotalStat().AttackRange + (Stat->GetAttackRadius() * 2);
}

float AMyEnemyNPC::GetAITurnSpeed()
{
	return 2.0f;
}

void AMyEnemyNPC::SetAIAttackDelegate(const FAICharacterAttackFinished& InOnAttackFinished)
{
	OnAttackFinished = InOnAttackFinished;
}

void AMyEnemyNPC::AttackByAI()
{
	ProcessComboCommand();
}

void AMyEnemyNPC::NotifyComboActionEnd()
{
	Super::NotifyComboActionEnd();
	OnAttackFinished.ExecuteIfBound();
}
