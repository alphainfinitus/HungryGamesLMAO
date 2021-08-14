// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

UCLASS()
class HUNGRYGAMESLMAO_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void PlaceActors(TSubclassOf<AActor> ToSpawn, int MinSpawn = 1, int MaxSpawn = 1, float Radius = 500, float MinScale = 1.f, float MaxScale = 1.f);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	bool CanSpawnAtLocation(FVector Location, float Radius);

	bool FindEmptyLocation(float Radius, FVector& OUTLocation);

	void PlaceActor(TSubclassOf<AActor> ToSpawn, FVector SpawnPoint, float Rotaion, float Scale);
};
