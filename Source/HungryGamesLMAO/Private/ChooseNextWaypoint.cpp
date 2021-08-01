// Fill out your copyright notice in the Description page of Project Settings.


#include "ChooseNextWaypoint.h"
#include "AIController.h"
#include "PatrolRoute.h" // TODO Remove coupling
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory){
	//UE_LOG(LogTemp, Warning, TEXT("AI Behavior Tree CPP"));

	//Get Patrol Points
	auto controlledPawn = OwnerComp.GetAIOwner()->GetPawn();
	auto patrolRoute = controlledPawn->FindComponentByClass<UPatrolRoute>();

	if (!ensure(patrolRoute)) { return EBTNodeResult::Failed; }

	auto patrolPoints = patrolRoute->GetPatrolPoints();

	if (patrolPoints.Num() < 1) {
		UE_LOG(LogTemp, Warning, TEXT("%s is missing patrol points"), *controlledPawn->GetName());
		return EBTNodeResult::Failed;
	}

	//Set next way-point
	auto blackboardComp = OwnerComp.GetBlackboardComponent();
	auto index = blackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);
	blackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, patrolPoints[index]);


	//Cycle the index
	auto nextIndex = (index + 1) % patrolPoints.Num();
	blackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, nextIndex);
	//blackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, patrolPoints[nextIndex]);

	return EBTNodeResult::Succeeded;
}
