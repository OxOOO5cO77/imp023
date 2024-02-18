// Copyright 2024 Impending Technologies

#include "UI/Menu/UI_MainMenu.h"

#include "Actor/Menu/GameStateMenu.h"

void UUI_MainMenu::OnInputMain(int const PlayerIndex)
{
	Super::OnInputMain(PlayerIndex);

	ScreenManager->NavigateTo("PlayerSelect");
}
