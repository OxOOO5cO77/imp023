// Copyright 2024 Impending Technologies

#include "Actor/Player/AIControllerGameplay.h"

#include "Actor/Object/Ball.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

class ABall;

void AAIControllerGameplay::BeginPlay()
{
	Super::BeginPlay();

	RunBehaviorTree(AIBehavior);

	UBlackboardComponent* const Blackboard = GetBlackboardComponent();

	AActor* const Ball = UGameplayStatics::GetActorOfClass(this, ABall::StaticClass());
	Blackboard->SetValueAsObject(TEXT("Ball"), Ball);
}

void AAIControllerGameplay::Tick(float const DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
