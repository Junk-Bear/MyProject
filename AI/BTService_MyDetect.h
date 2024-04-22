// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_MyDetect.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UBTService_MyDetect : public UBTService
{
	GENERATED_BODY()
public:
	UBTService_MyDetect();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
