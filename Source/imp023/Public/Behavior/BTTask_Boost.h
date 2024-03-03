// Copyright 2024 Impending Technologies

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlueprintBase.h"
#include "BTTask_Boost.generated.h"

/**
 *
 */
UCLASS()
class IMP023_API UBTTask_Boost : public UBTTask_BlueprintBase
{
	GENERATED_BODY()

public:
	UBTTask_Boost();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
