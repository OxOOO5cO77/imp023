// Copyright 2024 Impending Technologies
#include "UI/Gameplay/ScreenPreMatch.h"

#include "Actor/Gameplay/GameStateGameplay.h"

void UScreenPreMatch::OnInputMain(int const PlayerIndex)
{
	Super::OnInputMain(PlayerIndex);

	AGameStateGameplay* GameState = GetWorld()->GetGameState<AGameStateGameplay>();

	GameState->SetState(EGameplayGameState::PrePeriod);
}
