// Fill out your copyright notice in the Description page of Project Settings.


#include "MyEnemyNPC.h"

AMyEnemyNPC::AMyEnemyNPC()
{
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
