#include "SpawningSystem/Spawnable.h"

const TSubclassOf<AActor> USpawnable::GetSpawnableClass() const
{
	return SpawnableClass;
}