#pragma once

#include "CoreMinimal.h"
#include "SpawningSystem/Spawnable.h"
#include "SpawnableActor.generated.h"

UCLASS(Abstract)
class USpawnableActor : public USpawnable
{
	GENERATED_BODY()

	UPROPERTY(Category = "Spawnable", EditDefaultsOnly)
	TSubclassOf<AActor>  SpawnableClass;

	virtual const TSubclassOf<AActor> GetSpawnableClass() const override;
};
