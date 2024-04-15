#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "SpawningShapeIF.h"
#include "Components/BoxComponent.h"
#include "SpawningBoxShapeComponent.generated.h"

// A shape component that when added to an actor that has a spawner component, will act as a shape for a
UCLASS(ClassGroup="Collision", hidecategories=(Object,LOD,Lighting,TextureStreaming), editinlinenew, meta=(DisplayName="Spawning Box Shape", BlueprintSpawnableComponent), MinimalAPI)
class USpawningBoxShapeComponent : public UBoxComponent, public ISpawningShapeIF
{
	GENERATED_BODY()

public:
	USpawningBoxShapeComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	virtual void InitializeComponent() override;
	
	UPROPERTY(Category = "Spawning", EditAnywhere)
	FGameplayTagContainer SpawnableTags;
};
