// Copyright 2024 Impending Technologies


#include "UI/Gameplay/ScreenPrePeriod.h"

#include "Actor/Gameplay/GameStateGameplay.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void UScreenPrePeriod::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	AGameStateGameplay const* GameState = CastChecked<AGameStateGameplay>(UGameplayStatics::GetGameState(GetWorld()));

	TextPeriod->SetText(FText::Format(INVTEXT("Period {0}"), GameState->Period));
}

void UScreenPrePeriod::OnInputMain(int const PlayerIndex)
{
	Super::OnInputMain(PlayerIndex);

	AGameStateGameplay* GameState = CastChecked<AGameStateGameplay>(UGameplayStatics::GetGameState(GetWorld()));

	GameState->SetState(EGameplayGameState::PrePlay);
}
