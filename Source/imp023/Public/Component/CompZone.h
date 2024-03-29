// Copyright 2024 Impending Technologies

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Enum/EZone.h"
#include "CompZone.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class IMP023_API UCompZone : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UCompZone();

public:
	EZone Get() const { return Zone; }
	void Set(EZone const Value) { Zone = Value; }

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EZone Zone;
};
