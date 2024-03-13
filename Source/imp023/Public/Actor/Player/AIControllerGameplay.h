// Copyright 2024 Impending Technologies

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIControllerGameplay.generated.h"

/**
 *
 */
UCLASS()
class IMP023_API AAIControllerGameplay : public AAIController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	UBehaviorTree* AIBehavior;
};
