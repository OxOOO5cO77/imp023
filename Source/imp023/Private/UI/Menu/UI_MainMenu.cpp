// Copyright 2024 Impending Technologies

#include "UI/Menu/UI_MainMenu.h"

#include "Actor/Menu/GameStateMenu.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UUI_MainMenu::NativeOnInitialized()
{
	ButtonGo->OnClicked.AddDynamic(this, &UUI_MainMenu::OnClickGo);
}

void UUI_MainMenu::OnClickGo()
{
	AGameStateMenu* const Menu = Cast<AGameStateMenu>(UGameplayStatics::GetGameState(this));
	Menu->NavigateTo("PlayerSelect");
}
