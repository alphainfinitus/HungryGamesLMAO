// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HungryGamesLMAO/TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "PatrollingGuard.generated.h"

/**
 * 
 */
UCLASS()
class HUNGRYGAMESLMAO_API APatrollingGuard : public ATP_ThirdPersonCharacter
{
	GENERATED_BODY()

public:
	//TODO Create get function or remove
	UPROPERTY(EditInstanceOnly, Category="Patrol Route")
	TArray<AActor*> PatrolPointsCPP;
};
