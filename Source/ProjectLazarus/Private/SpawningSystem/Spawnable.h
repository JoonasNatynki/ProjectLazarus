#pragma once

#include "CoreMinimal.h"
#include "SpawnableProperty.h"
#include "Spawnable.generated.h"

class USpawnableProperty;

UCLASS(Blueprintable, Abstract)
class USpawnable : public UObject
{
	GENERATED_BODY()

public:
	virtual const TSubclassOf<AActor> GetSpawnableClass() const;
	template<class T> const T* FindSpawnProperty() const;

private:
	UPROPERTY(Category = "Spawnable", EditDefaultsOnly)
	FName SpawnableName;

	UPROPERTY(Category = "Spawnable", Instanced, EditDefaultsOnly)
	TArray<TObjectPtr<USpawnableProperty>> SpawnableProperties;
};

template <class T> const T* USpawnable::FindSpawnProperty() const
{
	return Cast<T>(*SpawnableProperties.FindByPredicate([](const TObjectPtr<USpawnableProperty> Prop)
	{
		return Prop->IsA(T::StaticClass());
	}));
};
