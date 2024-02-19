#include "SpawnerWorldSubSystem.h"

#include "Spawnable.h"
#include "SpawnableProperty.h"
#include "SpawnData.h"
#include "SpawningBoxShapeComponent.h"
#include "SpawnRequest.h"

DEFINE_LOG_CATEGORY(LogSpawnerWorldSubSystem)

bool USpawnerWorldSubSystem::Spawn(const FSpawnRequest& SpawnRequest) const
{
	return ProcessSpawnRequest(SpawnRequest);
}

USpawningBoxShapeComponent* USpawnerWorldSubSystem::GetRandomSpawningShapeComponentOnActor(
	const AActor* ActorWithSpawningShapes, const USpawnable* Spawnable)
{
	if (!ensure(IsValid(ActorWithSpawningShapes)))
	{
		nullptr;
	}

	TArray<USpawningBoxShapeComponent*> Shapes;
	ActorWithSpawningShapes->GetComponents<USpawningBoxShapeComponent>(Shapes);

	// If Spawnable is given, prune out invalid shapes for the spawnable
	if (IsValid(Spawnable))
	{
		if (const USpawnableShapeGameplayTagRequirement* Prop = Spawnable->FindSpawnProperty<USpawnableShapeGameplayTagRequirement>())
		{
			Shapes = Shapes.FilterByPredicate([Prop](const USpawningBoxShapeComponent* Comp)
			{
				return Comp->SpawnableTags.MatchesQuery(Prop->TagQuery);
			});
		}
	}
	
	if (!Shapes.IsEmpty())
	{
		const int32 Range = Shapes.Num();
		const int32 Rand = FMath::RandRange(0, Range - 1 );
		if (!ensureAlways(Shapes.IsValidIndex(Rand)))
		{
			return nullptr;
		}
	
		return Shapes[Rand];
	}
	
	return nullptr;
}

const FSpawnData USpawnerWorldSubSystem::ProcessSpawnRequest(const FSpawnRequest& SpawnRequest) const
{
	FSpawnData SpawnData;

	if (!IsValid(SpawnRequest.Spawnable))
	{
		UE_LOG(LogSpawnerWorldSubSystem, Warning, TEXT("A spawn request was processed that had no spawnable assigned! Instigator = (%s)"),
			*GetNameSafe(SpawnRequest.Instigator.Get()));
		
		return FSpawnData();
	}

	AActor* SpawnedActor = GetWorld()->SpawnActor(
		SpawnRequest.Spawnable->GetDefaultObject<USpawnable>()->GetSpawnableClass(),
		&SpawnRequest.SpawnTransform,
		SpawnRequest.SpawnParameters);
	
	if (!IsValid(SpawnedActor))
	{
		UE_LOG(LogSpawnerWorldSubSystem, Warning, TEXT("Spawn request (%s) processing was unsuccessful."), *SpawnRequest.ToString());
		return FSpawnData();
	}

	SpawnedActorLocationAdjustments_Internal(SpawnRequest, SpawnedActor);

	// Record data if we have to
	if (SpawnRequest.bRecordSpawnData)
	{
		SpawnData.SpawnedActor = SpawnedActor;
		SpawnData.SpawnedActorClass = SpawnRequest.Spawnable->GetDefaultObject<USpawnable>()->GetSpawnableClass();
	}

	UE_LOG(LogSpawnerWorldSubSystem, Log, TEXT("Spawned (%s)"), *SpawnData.ToString())

	return SpawnData;
}

void USpawnerWorldSubSystem::SpawnedActorLocationAdjustments_Internal(const FSpawnRequest& Request, AActor* SpawnedActor)
{
	if (Request.bTryToAdjustForEncroachingGeometry)
	{		
		FVector Adjustment;
		if (SpawnedActor->GetWorld()->EncroachingBlockingGeometry(
			SpawnedActor,
			Request.SpawnTransform.GetLocation(),
			Request.SpawnTransform.Rotator(),
			&Adjustment))
		{
			if (!Adjustment.IsZero())
			{
				SpawnedActor->AddActorWorldOffset(Adjustment);
			}
			else
			{
				FVector Loc = Request.SpawnTransform.GetLocation();
				if (SpawnedActor->GetWorld()->FindTeleportSpot(
					SpawnedActor,
					Loc
					,Request.SpawnTransform.Rotator()))
				{
					SpawnedActor->SetActorLocation(Loc);
				}
				else
				{
					UE_LOG(LogSpawnerWorldSubSystem, Warning, TEXT("Could not find a suitable spawn location for "
						"actor (%s) without encroaching geometry!"), *GetNameSafe(SpawnedActor));
				}
			}
		}	
	}
}
