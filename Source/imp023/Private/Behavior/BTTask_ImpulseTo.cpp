// Copyright 2024 Impending Technologies

#include "Behavior/BTTask_ImpulseTo.h"

#include "Actor/Player/AIControllerGameplay.h"
#include "Actor/Player/PlayerPawn.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetMathLibrary.h"

UBTTask_ImpulseTo::UBTTask_ImpulseTo()
{
	NodeName = TEXT("Impulse To");
}

EBTNodeResult::Type UBTTask_ImpulseTo::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	FName const Key = GetSelectedBlackboardKey();

	UBlackboardComponent const* const Blackboard = OwnerComp.GetBlackboardComponent();
	AActor const* const Target = CastChecked<AActor>(Blackboard->GetValueAsObject(Key));

	APlayerPawn const* const Pawn = CastChecked<APlayerPawn>(OwnerComp.GetAIOwner()->GetPawn());

	FVector const Dir = UKismetMathLibrary::GetDirectionUnitVector(Pawn->GetActorLocation(), Target->GetActorLocation());

	Pawn->Move(Dir);

	return EBTNodeResult::Succeeded;
}
