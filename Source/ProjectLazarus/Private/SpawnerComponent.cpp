#include "SpawnerComponent.h"

#include "IMovieSceneObjectSpawner.h"
#include "Components/ShapeComponent.h"
#include "SpawningSystem/SpawnerWorldSubSystem.h"
#include "SpawningSystem/SpawnRequest.h"

USpawnerComponent::USpawnerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USpawnerComponent::SpawnSpawnable(const TSubclassOf<USpawnable> Spawnable)
{
	if (const USpawnerWorldSubSystem* SWSS = GetWorld()->GetSubsystem<USpawnerWorldSubSystem>())
	{
		const FSpawnRequest Request(this, Spawnable);
		SWSS->Spawn(Request);
	}
}

void USpawnerComponent::Spawn(const FSpawnRequest SpawnRequest) const
{
	if (const USpawnerWorldSubSystem* SWSS = GetWorld()->GetSubsystem<USpawnerWorldSubSystem>())
	{
		SWSS->Spawn(SpawnRequest);
	}
}

void USpawnerComponent::AddSpawnableShape(const UShapeComponent* ShapeComponent)
{
	if (ensureAlways(IsValid(ShapeComponent)))
	{
		SpawnableShapes.AddUnique(ShapeComponent);
	}
}

bool USpawnerComponent::HasSpawnableShapes() const
{
	return SpawnableShapes.Num() > 0;
}

void USpawnerComponent::BeginPlay()
{
	Super::BeginPlay();
}
