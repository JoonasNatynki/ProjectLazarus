#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Spawnable.generated.h"

UCLASS(Blueprintable, Abstract)
class USpawnable : public UObject
{
	GENERATED_BODY()

public:
	virtual const TSubclassOf<AActor> GetSpawnableClass() const;
	
private:
	UPROPERTY(Category = "Spawnable", EditDefaultsOnly)
	TSubclassOf<AActor>  SpawnableClass;

	UPROPERTY(Category = "Spawnable", EditDefaultsOnly)
	FName SpawnableName;
};
