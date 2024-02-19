#include "SpawningSystem/SpawnablePoolComponent.h"
#include "Spawnable.h"

USpawnablePoolComponent::USpawnablePoolComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USpawnablePoolComponent::AddSpawnableToPool(const TSubclassOf<USpawnable> Spawnable)
{
	SpawnablesPool.AddUnique(Spawnable);
}

TSubclassOf<USpawnable> USpawnablePoolComponent::GetRandomValidSpawnable() const
{
	const int32 Range = SpawnablesPool.Num();
	const int32 Rand = FMath::RandRange(0, Range - 1);
	return (SpawnablesPool.IsValidIndex(Rand)) ? (SpawnablesPool[Rand]) : (nullptr);
}
