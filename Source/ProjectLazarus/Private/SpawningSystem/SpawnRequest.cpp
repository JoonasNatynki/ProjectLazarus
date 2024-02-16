#include "SpawnRequest.h"
#include "SpawnerComponent.h"
#include "Spawnable.h"

FSpawnRequest::FSpawnRequest(const TSubclassOf<USpawnable> Spawnable)
{
	ActorClassToSpawn = Spawnable->GetDefaultObject<USpawnable>()->GetSpawnableClass();
}

FSpawnRequest::FSpawnRequest(const TSubclassOf<AActor> Class)
{
	ActorClassToSpawn = Class;
}

FSpawnRequest::FSpawnRequest(const USpawnerComponent* SpawnerComponent)
{
	if (!ensure(IsValid(SpawnerComponent)) || !ensure(IsValid(SpawnerComponent->Spawnable)))
	{
		return;
	}
	
	ActorClassToSpawn = SpawnerComponent->Spawnable->GetDefaultObject<USpawnable>()->GetSpawnableClass();
	SpawnTransform = SpawnerComponent->GetComponentTransform();
}

const FString FSpawnRequest::ToString() const
{
	FString ReturnString = GetNameSafe(ActorClassToSpawn);
	return ReturnString;
}
