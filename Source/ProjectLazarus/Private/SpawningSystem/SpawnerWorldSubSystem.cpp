#include "SpawnerWorldSubSystem.h"
#include "SpawnData.h"
#include "SpawnRequest.h"

DEFINE_LOG_CATEGORY(LogSpawningWorldSubSystem)

bool USpawnerWorldSubSystem::Spawn(const FSpawnRequest& SpawnRequest) const
{
	return ProcessSpawnRequest(SpawnRequest);
}

const FSpawnData USpawnerWorldSubSystem::ProcessSpawnRequest(const FSpawnRequest& SpawnRequest) const
{
	FSpawnData SpawnData;

	AActor* SpawnedActor = GetWorld()->SpawnActor(SpawnRequest.ActorClassToSpawn, &SpawnRequest.SpawnTransform, SpawnRequest.SpawnParameters);
	if (!IsValid(SpawnedActor))
	{
		UE_LOG(LogSpawningWorldSubSystem, Warning, TEXT("Spawn request (%s) processing was unsuccessful."), *SpawnRequest.ToString());
	}

	if (SpawnRequest.bRecordSpawnData)
	{
		SpawnData.SpawnedActor = SpawnedActor;
		SpawnData.SpawnedActorClass = SpawnRequest.ActorClassToSpawn;
	}

	UE_LOG(LogSpawningWorldSubSystem, Log, TEXT("Spawned (%s)"), *SpawnData.ToString())

	return SpawnData;
}
