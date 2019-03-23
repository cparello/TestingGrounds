// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "PatrolRoute.h"
#include "AIController.h"


EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//get patrol route
	auto PatrolRoute = OwnerComp.GetAIOwner()->GetPawn()->FindComponentByClass<UPatrolRoute>();

	// protect against no patrol route component
	if (!ensure(PatrolRoute)) return EBTNodeResult::Failed;

	// protect against empty patrol routes
	auto PatrolPoints = PatrolRoute->GetPatrolPoints();
	if(PatrolPoints.Num())
	{
		UE_LOG(LogTemp, Warning, TEXT("a guard has empty patrol routes"))
	}

	//set next way point
	auto BlackboardComp = OwnerComp.GetBlackboardComponent();
	auto Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);
	BlackboardComp->SetValueAsObject(WaypoinKey.SelectedKeyName, PatrolPoints[Index]);

	//cycle the index
	auto NextIndex = (Index + 1) % PatrolPoints.Num();
	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, NextIndex);

	return EBTNodeResult::Succeeded;
}
