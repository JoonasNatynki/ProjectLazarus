#include "SpawnRequest.h"
#include "SpawnerComponent.h"
#include "Spawnable.h"
#include "SpawnerWorldSubSystem.h"

FSpawnRequest::FSpawnRequest(
	const TSubclassOf<USpawnable>& InSpawnable,
	const FTransform& InSpawnTransform,
	const FActorSpawnParameters& InSpawnParameters,
	const bool InbRecordSpawnData,
	const bool InbTryToAdjustForEncroachingGeometry)
{
	Spawnable = InSpawnable;
	SpawnTransform = InSpawnTransform;
	SpawnParameters = InSpawnParameters;
	bRecordSpawnData = InbRecordSpawnData;
	bTryToAdjustForEncroachingGeometry = InbTryToAdjustForEncroachingGeometry;
}

FSpawnRequest::FSpawnRequest(const USpawnerComponent* SpawnerComponent, const TSubclassOf<USpawnable> InSpawnable)
{
	if (!ensureAlways(IsValid(SpawnerComponent)) || !ensureAlways(IsValid(InSpawnable)))
	{
		return;
	}
	
	bTryToAdjustForEncroachingGeometry = SpawnerComponent->bTryToAdjustForEncroachingGeometry;
	Instigator = SpawnerComponent->GetOwner();
	Spawnable = InSpawnable;

	if (SpawnerComponent->bUseSpawnableShapes && SpawnerComponent->HasSpawnableShapes())
	{
		const USpawningBoxShapeComponent* RandShape = USpawnerWorldSubSystem::GetRandomSpawningShapeComponentOnActor(
				SpawnerComponent->GetOwner(),
				Spawnable->GetDefaultObject<USpawnable>());

		if (IsValid(RandShape))
		{
			const FVector RandPointInShape = RandShape->GetRandomPointInShapeComponent(SpawnerComponent->bTryFindSurfaceToPlace);
			SpawnTransform.SetLocation(RandPointInShape);
		}
	}
	else
	{
		SpawnTransform = SpawnerComponent->GetComponentTransform();
	}
}

const FString FSpawnRequest::ToString() const
{
	FString ReturnString = GetNameSafe(Spawnable);
	return ReturnString;
}
