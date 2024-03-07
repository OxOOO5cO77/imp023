// Copyright 2024 Impending Technologies


#include "UI/Menu/ScreenHumans.h"

#include "Actor/Menu/GameStateMenu.h"
#include "Components/TextBlock.h"
#include "UI/Manager/ScreenManager.h"

static constexpr uint32 GMaxHumans = 8;

void UScreenHumans::NativeConstruct()
{
	Super::NativeConstruct();

	TrackedHumans = 1;
}

void UScreenHumans::OnInputMain(int const PlayerIndex)
{
	Super::OnInputMain(PlayerIndex);

	AGameStateMenu* GameState = GetWorld()->GetGameState<AGameStateMenu>();
	check(GameState);

	GameState->SetExpectedHumans(TrackedHumans);

	ScreenManager->NavigateTo("TeamSelect");
}

void UScreenHumans::OnInputBack(int const PlayerIndex)
{
	Super::OnInputBack(PlayerIndex);

	ScreenManager->NavigateTo("MainMenu");
}


void UScreenHumans::OnInputLeft(int const PlayerIndex)
{
	Super::OnInputLeft(PlayerIndex);

	WrapTrackedHumans(-1);

	UpdateText();
}

void UScreenHumans::OnInputRight(int const PlayerIndex)
{
	Super::OnInputRight(PlayerIndex);

	WrapTrackedHumans(1);

	UpdateText();
}

void UScreenHumans::UpdateText() const
{
	TextCount->SetText(FText::AsNumber(TrackedHumans));
	TextHuman->SetText(TrackedHumans == 1 ? INVTEXT("Human") : INVTEXT("Humans"));
}

void UScreenHumans::WrapTrackedHumans(int const Amount)
{
	--TrackedHumans;
	TrackedHumans = (TrackedHumans + GMaxHumans + Amount) % GMaxHumans;
	++TrackedHumans;
}
