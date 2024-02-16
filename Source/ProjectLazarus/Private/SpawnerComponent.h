#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SpawnerComponent.generated.h"

struct FSpawnRequest;
class USpawnable;

// Spawner component that is capable of spawning many things
UCLASS( ClassGroup=(Spawning), meta=(BlueprintSpawnableComponent))
class USpawnerComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	USpawnerComponent();

	UPROPERTY(Category = "Spawner", EditAnywhere)
	TSubclassOf<USpawnable> Spawnable;
	
	UPROPERTY(Category = "Spawner", EditAnywhere)
	bool bAutoSpawn = false;

	UFUNCTION(BlueprintCallable)
	void Spawn(const FSpawnRequest SpawnRequest) const;

protected:

	void BeginPlay() override;
};
