#include "SpawnerComponent.h"
#include "SpawningSystem/SpawnerWorldSubSystem.h"
#include "SpawningSystem/SpawnRequest.h"

USpawnerComponent::USpawnerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USpawnerComponent::Spawn(const FSpawnRequest SpawnRequest) const
{
	if (const USpawnerWorldSubSystem* SWSS = GetWorld()->GetSubsystem<USpawnerWorldSubSystem>())
	{
		SWSS->Spawn(SpawnRequest);
	}
}

void USpawnerComponent::BeginPlay()
{
	Super::BeginPlay();

	if (bAutoSpawn)
	{
		if (const USpawnerWorldSubSystem* SWSS = GetWorld()->GetSubsystem<USpawnerWorldSubSystem>())
		{
			const FSpawnRequest Request(this);
			SWSS->Spawn(Request);
		}
	}
}
