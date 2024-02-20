// Copyright 2024 Impending Technologies


#include "UI/Gameplay/ScreenPrePeriod.h"

#include "Actor/Gameplay/GameStateGameplay.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void UScreenPrePeriod::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	AGameStateGameplay* GameState = Cast<AGameStateGameplay>(UGameplayStatics::GetGameState(GetWorld()));
	check(GameState);

	TextPeriod->SetText(FText::Format(INVTEXT("Period {0}"), GameState->Period));
}

void UScreenPrePeriod::OnInputMain(int const PlayerIndex)
{
	Super::OnInputMain(PlayerIndex);

	AGameStateGameplay* GameState = Cast<AGameStateGameplay>(UGameplayStatics::GetGameState(GetWorld()));
	check(GameState);

	GameState->SetState(EGameplayGameState::PrePlay);
}
