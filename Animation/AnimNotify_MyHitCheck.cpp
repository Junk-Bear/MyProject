// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_MyHitCheck.h"
#include "Interface/MyAttackAnimationInterface.h"

void UAnimNotify_MyHitCheck::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (MeshComp)
	{
		IMyAttackAnimationInterface* AttackPawn = Cast<IMyAttackAnimationInterface>(MeshComp->GetOwner());
		if (AttackPawn)
		{
			AttackPawn->AttackHitCheck();
		}
	}
}
