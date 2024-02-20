// Copyright 2024 Impending Technologies


#include "UI/Gameplay/ScreenPreMatch.h"

#include "Actor/Gameplay/GameStateGameplay.h"
#include "Kismet/GameplayStatics.h"

void UScreenPreMatch::OnInputMain(int const PlayerIndex)
{
	Super::OnInputMain(PlayerIndex);

	AGameStateGameplay* GameState = CastChecked<AGameStateGameplay>(UGameplayStatics::GetGameState(GetWorld()));

	GameState->SetState(EGameplayGameState::PrePeriod);
}
