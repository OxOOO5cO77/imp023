// Copyright 2024 Impending Technologies


#include "Behavior/BTTask_Boost.h"

#include "Actor/Player/AIControllerGameplay.h"
#include "Actor/Player/PlayerPawn.h"

UBTTask_Boost::UBTTask_Boost()
{
	NodeName = TEXT("Boost");
}

EBTNodeResult::Type UBTTask_Boost::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	APlayerPawn* const Pawn = CastChecked<APlayerPawn>(OwnerComp.GetAIOwner()->GetPawn());
	Pawn->Boost();

	return EBTNodeResult::Succeeded;
}
