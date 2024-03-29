// Copyright 2024 Impending Technologies

#include "Actor/Volume/VolumeZone.h"

#include "Actor/Gameplay/GameStateGameplay.h"
#include "Actor/Object/Ball.h"
#include "Component/CompZone.h"

AVolumeZone::AVolumeZone()
{
	CompZone = CreateDefaultSubobject<UCompZone>(TEXT("Zone"));

	OnActorBeginOverlap.AddDynamic(this, &AVolumeZone::OnOverlap);
}

void AVolumeZone::BeginPlay()
{
	Super::BeginPlay();

	GameState = GetWorld()->GetGameState<AGameStateGameplay>();
}


void AVolumeZone::OnOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	ABall const* const Ball = Cast<ABall>(OtherActor);
	if (Ball == nullptr)
	{
		return;
	}

	GameState->ChangeZone(CompZone->Get());
}
