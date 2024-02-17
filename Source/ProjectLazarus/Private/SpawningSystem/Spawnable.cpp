#include "SpawningSystem/Spawnable.h"

const TSubclassOf<AActor> USpawnable::GetSpawnableClass() const
{
	int32 Test = 0;
	return SpawnableClass;
}