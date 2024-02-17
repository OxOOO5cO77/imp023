// Copyright 2024 Impending Technologies

#include "Actor/Object/Ball.h"

#include "Actor/Gameplay/GameStateGameplay.h"
#include "Kismet/GameplayStatics.h"

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

	AGameStateGameplay* GameState = Cast<AGameStateGameplay>(UGameplayStatics::GetGameState(this));
	OnStateChangeHandle = GameState->OnStateChange().AddUObject(this, &ABall::OnStateChange);
}

void ABall::EndPlay(EEndPlayReason::Type const EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	AGameStateGameplay* GameState = Cast<AGameStateGameplay>(UGameplayStatics::GetGameState(this));
	GameState->OnStateChange().Remove(OnStateChangeHandle);;
}

FVector ABall::GetLocationTargetForBoost(FVector const& Source) const
{
	FVector const Distance = Source - GetActorLocation();
	double const Time = Distance.Length() / 1000.0f;
	return GetActorLocation() + CompStaticMeshBase->GetComponentVelocity() * Time;
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
