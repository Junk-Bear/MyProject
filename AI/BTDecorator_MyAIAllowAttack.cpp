// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTDecorator_MyAIAllowAttack.h"
#include "MyAIDefine.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Interface/MyEnemyAIInterface.h"

UBTDecorator_MyAIAllowAttack::UBTDecorator_MyAIAllowAttack()
{
	NodeName = TEXT("CanAttack");
}

bool UBTDecorator_MyAIAllowAttack::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn)
	{
		return false;
	}

	IMyEnemyAIInterface* AIPawn = Cast<IMyEnemyAIInterface>(ControllingPawn);
	if (nullptr == AIPawn)
	{
		return false;
	}

	APawn* Target = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(BBKEY_TARGET));
	if (nullptr == Target)
	{
		return false;
	}

	float DistanceToTarget = ControllingPawn->GetDistanceTo(Target);
	float AttackRangeWithRadius = AIPawn->GetAIAttackRange();
	bResult = (DistanceToTarget <= AttackRangeWithRadius);
	return bResult;
}
