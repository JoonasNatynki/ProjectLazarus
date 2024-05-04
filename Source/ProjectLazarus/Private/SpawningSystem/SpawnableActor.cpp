#include "SpawningSystem/SpawnableActor.h"

const TSubclassOf<AActor> USpawnableActor::GetSpawnableClass() const
{
	return SpawnableClass;
}