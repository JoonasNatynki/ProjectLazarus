#pragma once

#include "Runtime/Engine/Classes/Engine/World.h"
#include "SpawnRequest.generated.h"

class AActor;
class USpawnerComponent;
class USpawnable;

USTRUCT(Blueprintable)
struct FSpawnRequest
{
	GENERATED_BODY()

	FSpawnRequest() {}
	explicit FSpawnRequest(const TSubclassOf<USpawnable> Spawnable);
	explicit FSpawnRequest(const TSubclassOf<AActor> Class);
	explicit FSpawnRequest(const USpawnerComponent* SpawnerComponent);

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<AActor> ActorClassToSpawn;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FTransform SpawnTransform;
	
	FActorSpawnParameters SpawnParameters;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bRecordSpawnData = true;

	const FString ToString() const;
};