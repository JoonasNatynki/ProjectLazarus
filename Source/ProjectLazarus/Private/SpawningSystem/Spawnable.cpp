#include "SpawningSystem/Spawnable.h"

#include "EntitySystem/MovieSceneEntitySystemRunner.h"

const TSubclassOf<AActor> USpawnable::GetSpawnableClass() const
{
	return SpawnableClass;
}