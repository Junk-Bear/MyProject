// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_MyPatrol.generated.h"

/**
 *
 */
UCLASS()
class MYPROJECT_API UBTTask_MyPatrol : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_MyPatrol();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
