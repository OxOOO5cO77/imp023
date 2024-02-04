// Copyright 2024 Impending Technologies

#include "Actor/Volume/VolumeHall.h"

#include "Actor/Object/Ball.h"

AVolumeHall::AVolumeHall()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PrePhysics;

	OnActorBeginOverlap.AddDynamic(this, &AVolumeHall::OnOverlapBegin);
	OnActorEndOverlap.AddDynamic(this, &AVolumeHall::OnOverlapEnd);

	TrackedBall = nullptr;

	RegisterAllActorTickFunctions(true, false);
}

void AVolumeHall::BeginPlay()
{
	Super::BeginPlay();

	SetActorTickEnabled(false);
}

void AVolumeHall::Tick(float const DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TrackedBall)
	{
		TrackedBall->Boost(Impulse * DeltaTime);
	}
}

void AVolumeHall::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	ABall* const Ball = Cast<ABall>(OtherActor);
	if (Ball == nullptr)
	{
		return;
	}

	OverlappedActor->SetActorTickEnabled(true);
	TrackedBall = Ball;
}

void AVolumeHall::OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor)
{
	ABall const* const Ball = Cast<ABall>(OtherActor);
	if (Ball == nullptr)
	{
		return;
	}

	OverlappedActor->SetActorTickEnabled(true);
	TrackedBall = nullptr;
}
