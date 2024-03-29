// Copyright 2024 Impending Technologies

#include "Actor/Player/AIControllerGameplay.h"

#include "Actor/Object/Ball.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void AAIControllerGameplay::BeginPlay()
{
	Super::BeginPlay();

	RunBehaviorTree(AIBehavior);

	UBlackboardComponent* const BlackboardComponent = GetBlackboardComponent();

	AActor* const Ball = UGameplayStatics::GetActorOfClass(this, ABall::StaticClass());
	BlackboardComponent->SetValueAsObject(TEXT("Ball"), Ball);
}
