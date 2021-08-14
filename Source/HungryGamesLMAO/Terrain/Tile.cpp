// Fill out your copyright notice in the Description page of Project Settings.


#include "./Tile.h"
#include "DrawDebugHelpers.h"

// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ATile::PlaceActors(TSubclassOf<AActor> ToSpawn, int MinSpawn, int MaxSpawn, float Radius) {
	

	int NumberToSpawn = FMath::RandRange(MinSpawn, MaxSpawn);

	for (size_t i = 0; i < NumberToSpawn; i++){
		FVector EmptyLocation;
		bool foundEmptyLocation = FindEmptyLocation(Radius, EmptyLocation);

		if (foundEmptyLocation) {
			PlaceActor(ToSpawn, EmptyLocation);
		}
	}
}

bool ATile::FindEmptyLocation(float Radius, FVector& OUTLocation) {
	FVector Min(0, -2000, 100);
	FVector Max(4000, 2000, 100);
	FBox Bounds(Min, Max);

	const int MAX_ATTEMPTS = 100;

	for (size_t i = 0; i < MAX_ATTEMPTS; i++) {
		FVector candidatePoint = FMath::RandPointInBox(Bounds);

		if (CanSpawnAtLocation(candidatePoint, Radius)) {
			OUTLocation = candidatePoint;
			return true;
		}
	}
	return false;

}

void ATile::PlaceActor(TSubclassOf<AActor> ToSpawn, FVector SpawnPoint) {
	AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(ToSpawn);
	SpawnedActor->SetActorRelativeLocation(SpawnPoint);
	SpawnedActor->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ATile::CanSpawnAtLocation(FVector Location, float Radius) {
	FHitResult hitResult;

	FVector GlobalLocation = ActorToWorld().TransformPosition(Location);

	bool hasHit = GetWorld()->SweepSingleByChannel(hitResult, GlobalLocation, GlobalLocation, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel2, FCollisionShape::MakeSphere(Radius));

	FColor resultColour = hasHit ? FColor::Red : FColor::Green;

	DrawDebugCapsule(GetWorld(), GlobalLocation, 0, Radius, FQuat::Identity, resultColour, true, 100);

	return !hasHit;
}

