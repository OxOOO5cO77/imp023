// Copyright 2024 Impending Technologies


#include "Subsystem/MenuTransitionSubsystem.h"

FString const& UMenuTransitionSubsystem::GetStartScreen() const
{
	return StartScreen;
}

void UMenuTransitionSubsystem::SetStartScreen(FString const& Screen)
{
	StartScreen = Screen;
}
