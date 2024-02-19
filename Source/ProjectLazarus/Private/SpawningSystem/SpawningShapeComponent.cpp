#include "SpawningBoxShapeComponent.h"
#include "SpawnerComponent.h"

USpawningBoxShapeComponent::USpawningBoxShapeComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bWantsInitializeComponent = true;
}

void USpawningBoxShapeComponent::InitializeComponent()
{
	Super::InitializeComponent();

	if (USpawnerComponent* SpawnComp = GetOwner()->FindComponentByClass<USpawnerComponent>())
	{
		SpawnComp->AddSpawnableShape(this);
	}
}
