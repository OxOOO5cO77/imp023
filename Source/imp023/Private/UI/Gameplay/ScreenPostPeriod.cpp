// Copyright 2024 Impending Technologies


#include "UI/Gameplay/ScreenPostPeriod.h"

#include "Actor/Gameplay/GameStateGameplay.h"
#include "Kismet/GameplayStatics.h"

class AGameStateGameplay;

void UScreenPostPeriod::OnInputMain(int const PlayerIndex)
{
	Super::OnInputMain(PlayerIndex);

	AGameStateGameplay* GameState = Cast<AGameStateGameplay>(UGameplayStatics::GetGameState(GetWorld()));
	check(GameState);

	EGameplayGameState NewState = GameState->Period == 3 ? EGameplayGameState::PostMatch : EGameplayGameState::PrePeriod;
	GameState->SetState(NewState);
}
