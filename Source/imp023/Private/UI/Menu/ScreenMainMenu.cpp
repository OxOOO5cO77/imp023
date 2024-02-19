// Copyright 2024 Impending Technologies

#include "UI/Menu/ScreenMainMenu.h"

#include "UI/Manager/ScreenManager.h"

void UScreenMainMenu::OnInputMain(int const PlayerIndex)
{
	Super::OnInputMain(PlayerIndex);

	ScreenManager->NavigateTo("PlayerSelect");
}
