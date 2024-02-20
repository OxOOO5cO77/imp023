// Copyright 2024 Impending Technologies

#include "Actor/Volume/VolumeGoal.h"

#include "Actor/Gameplay/GameStateGameplay.h"
#include "Actor/Object/Ball.h"
#include "Component/CompTeam.h"
#include "Kismet/GameplayStatics.h"

AVolumeGoal::AVolumeGoal()
{
	CompTeam = CreateDefaultSubobject<UCompTeam>(TEXT("Team"));

	OnActorBeginOverlap.AddDynamic(this, &AVolumeGoal::OnOverlap);
}

void AVolumeGoal::BeginPlay()
{
	Super::BeginPlay();

	GameState = CastChecked<AGameStateGameplay>(UGameplayStatics::GetGameState(this));
}

void AVolumeGoal::OnOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	ABall const* const Ball = Cast<ABall>(OtherActor);
	if (Ball == nullptr)
	{
		return;
	}

	GameState->ScoreGoal(CompTeam->Get());
}
