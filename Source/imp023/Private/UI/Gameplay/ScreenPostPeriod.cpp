// Copyright 2024 Impending Technologies


#include "UI/Gameplay/ScreenPostPeriod.h"

#include "Actor/Gameplay/GameStateGameplay.h"
#include "Kismet/GameplayStatics.h"

class AGameStateGameplay;

void UScreenPostPeriod::OnInputMain(int const PlayerIndex)
{
	Super::OnInputMain(PlayerIndex);

	AGameStateGameplay* GameState = CastChecked<AGameStateGameplay>(UGameplayStatics::GetGameState(GetWorld()));

	EGameplayGameState const NewState = GameState->Period == 3 ? EGameplayGameState::PostMatch : EGameplayGameState::PrePeriod;
	GameState->SetState(NewState);
}
