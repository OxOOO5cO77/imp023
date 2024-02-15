// Copyright 2024 Impending Technologies

#include "UI/Menu/UI_MainMenu.h"

#include "Actor/Menu/GameStateMenu.h"
#include "Kismet/GameplayStatics.h"

void UUI_MainMenu::NativeOnInitialized()
{
}

void UUI_MainMenu::OnInputMain(int const PlayerIndex)
{
	Super::OnInputMain(PlayerIndex);

	AGameStateMenu* const Menu = Cast<AGameStateMenu>(UGameplayStatics::GetGameState(this));
	Menu->NavigateTo("PlayerSelect");
}
