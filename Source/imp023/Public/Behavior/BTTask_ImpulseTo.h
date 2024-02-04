// Copyright 2024 Impending Technologies

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_ImpulseTo.generated.h"

/**
 *
 */
UCLASS()
class IMP023_API UBTTask_ImpulseTo : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_ImpulseTo();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
