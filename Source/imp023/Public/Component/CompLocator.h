// Copyright 2024 Impending Technologies

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Enum/ELocator.h"
#include "CompLocator.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class IMP023_API UCompLocator : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UCompLocator();

public:
	ELocator Get() const { return Locator; }
	void Set(ELocator const Value) { Locator = Value; }

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	ELocator Locator;
};
