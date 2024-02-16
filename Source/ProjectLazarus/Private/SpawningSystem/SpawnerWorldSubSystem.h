#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "SpawnData.h"
#include "SpawnerWorldSubSystem.generated.h"

class USpawnable;
struct FSpawnData;
struct FSpawnRequest;

DECLARE_LOG_CATEGORY_EXTERN(LogSpawningWorldSubSystem, Log, All)

UCLASS()
class USpawnerWorldSubSystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	bool Spawn(const FSpawnRequest& SpawnRequest) const;
	
private:
	const FSpawnData ProcessSpawnRequest(const FSpawnRequest& SpawnRequest) const;
};

static TArray<FSpawnData> SpawnDatas;
