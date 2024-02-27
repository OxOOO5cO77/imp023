// Copyright 2024 Impending Technologies


#include "Component/CompTeamPeriodChange.h"

#include "Actor/Gameplay/GameStateGameplay.h"
#include "Utils/GameplayUtils.h"


// Sets default values for this component's properties
UCompTeamPeriodChange::UCompTeamPeriodChange()
	: CompTeam(nullptr)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UCompTeamPeriodChange::BeginPlay()
{
	Super::BeginPlay();

	AGameStateGameplay* GameState = GetWorld()->GetGameState<AGameStateGameplay>();
	check(GameState);

	GameState->StateChangeEvent.AddUObject(this, &UCompTeamPeriodChange::OnStateChange);

	CompTeam = GetOwner()->GetComponentByClass<UCompTeam>();
	check(CompTeam);
}

void UCompTeamPeriodChange::OnStateChange(EGameplayGameState const GameplayGameState) const
{
	if (GameplayGameState == EGameplayGameState::PrePeriod)
	{
		AGameStateGameplay const* const GameState = GetWorld()->GetGameState<AGameStateGameplay>();
		CompTeam->Set(FGameplayUtils::MapPeriodTeamToTeam(GameState->Period, CompTeam->Get()));
	}
}
