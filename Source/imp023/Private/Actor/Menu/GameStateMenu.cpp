// Copyright 2024 Impending Technologies

#include "Actor/Menu/GameStateMenu.h"

#include "Blueprint/UserWidget.h"

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
		CurScreen = CreateWidget<UUserWidget>(GetWorld(), Destination);
		if (CurScreen != nullptr)
		{
			CurScreen->AddToViewport();
		}
	}
}
