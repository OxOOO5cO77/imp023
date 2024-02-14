// Copyright 2024 Impending Technologies

#include "Actor/Menu/GameStateMenu.h"

#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerState.h"
#include "UI/Menu/Screen.h"

AGameStateMenu::AGameStateMenu()
{
	CurScreen = nullptr;
}

void AGameStateMenu::BeginPlay()
{
	Super::BeginPlay();

	NavigateTo(Default);
}

void AGameStateMenu::NavigateTo(FString const& Screen)
{
	check(ScreenMap.Contains(Screen));

	if (CurScreen != nullptr)
	{
		CurScreen->RemoveFromParent();
		CurScreen = nullptr;
	}

	TSubclassOf<UUserWidget> const Destination = ScreenMap[Screen];

	if (Destination != nullptr)
	{
		CurScreen = CreateWidget<UScreen>(GetWorld(), Destination);
		if (CurScreen != nullptr)
		{
			CurScreen->AddToViewport();
		}
	}
}

int AGameStateMenu::ControllerIndex(APlayerControllerMenu const* PlayerControllerMenu) const
{
	APlayerState* State = PlayerControllerMenu->GetPlayerState<APlayerState>();
	return PlayerArray.IndexOfByPredicate([State](APlayerState const* Other) { return State == Other; });
}

void AGameStateMenu::ProcessInputMain(APlayerControllerMenu const* PlayerControllerMenu) const
{
	CurScreen->HandleInputMain(ControllerIndex(PlayerControllerMenu));
}

void AGameStateMenu::ProcessInputAlt(APlayerControllerMenu const* PlayerControllerMenu) const
{
	CurScreen->HandleInputAlt(ControllerIndex(PlayerControllerMenu));
}

void AGameStateMenu::ProcessInputBack(APlayerControllerMenu const* PlayerControllerMenu) const
{
	CurScreen->HandleInputBack(ControllerIndex(PlayerControllerMenu));
}
