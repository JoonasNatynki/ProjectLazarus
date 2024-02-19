#pragma once

#include "GameplayTagContainer.h"
#include "SpawnableProperty.generated.h"

UCLASS(Abstract)
class USpawnableProperty : public UObject
{
	GENERATED_BODY()
};

UCLASS(DefaultToInstanced, EditInlineNew)
class USpawnableShapeGameplayTagRequirement : public USpawnableProperty
{
	GENERATED_BODY()

public:
	// Needs to pass in order for the spawn to be allowed
	UPROPERTY(EditAnywhere)
	FGameplayTagQuery TagQuery;
};

