// Copyright 2024 Impending Technologies

#include "Actor/Object/Ball.h"

#include "Actor/Gameplay/GameStateGameplay.h"

// Sets default values
ABall::ABall()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CompStaticMeshBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ball"));
	RootComponent = CompStaticMeshBase;
}

void ABall::BeginPlay()
{
	Super::BeginPlay();

	AGameStateGameplay* GameState = GetWorld()->GetGameState<AGameStateGameplay>();
	OnStateChangeHandle = GameState->StateChangeEvent.AddUObject(this, &ABall::OnStateChange);
}

void ABall::EndPlay(EEndPlayReason::Type const EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	AGameStateGameplay* GameState = GetWorld()->GetGameState<AGameStateGameplay>();
	GameState->StateChangeEvent.Remove(OnStateChangeHandle);;
}

FVector ABall::GetLocationTargetForBoost(FVector const& Source, float const Rate) const
{
	FVector const BallLocation = GetActorLocation();
	float const Distance = (Source - BallLocation).Length();
	float const Time = Distance / Rate;
	return BallLocation + CompStaticMeshBase->GetComponentVelocity() * Time;
}

void ABall::Boost(FVector const& Boost) const
{
	FVector Velocity = CompStaticMeshBase->GetComponentVelocity();
	Velocity.Normalize();
	CompStaticMeshBase->AddImpulse(Velocity * Boost, NAME_None, true);
}

void ABall::ResetBall()
{
	SetActorLocation(FVector::ZeroVector);
	CompStaticMeshBase->SetPhysicsLinearVelocity(FVector::ZeroVector);
}

void ABall::OnStateChange(EGameplayGameState const State)
{
	switch (State)
	{
		case EGameplayGameState::PrePeriod:
		case EGameplayGameState::PrePlay:
			ResetBall();
			break;
		default:
			break;
	}
}
