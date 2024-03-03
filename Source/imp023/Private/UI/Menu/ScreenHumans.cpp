// Copyright 2024 Impending Technologies


#include "UI/Menu/ScreenHumans.h"

#include "Actor/Menu/GameStateMenu.h"
#include "UI/Manager/ScreenManager.h"

void UScreenHumans::OnInputMain(int const PlayerIndex)
{
	Super::OnInputMain(PlayerIndex);

	AGameStateMenu* GameState = GetWorld()->GetGameState<AGameStateMenu>();
	check(GameState);

	GameState->SetExpectedHumans(1);

	ScreenManager->NavigateTo("TeamSelect");
}

void UScreenHumans::OnInputBack(int const PlayerIndex)
{
	Super::OnInputBack(PlayerIndex);

	ScreenManager->NavigateTo("MainMenu");

}
