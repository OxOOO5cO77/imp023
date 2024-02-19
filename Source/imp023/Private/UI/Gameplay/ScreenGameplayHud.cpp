// Copyright 2024 Impending Technologies

#include "UI/Gameplay/ScreenGameplayHud.h"

#include "Actor/Gameplay/GameStateGameplay.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void UScreenGameplayHud::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	AGameStateGameplay* const GameState = Cast<AGameStateGameplay>(UGameplayStatics::GetGameState(GetWorld()));
	check(GameState);

	OnUpdateScoresHandle = GameState->UpdateScoresEvent.AddUObject(this, &UScreenGameplayHud::OnUpdateScores);
	GameState->BroadcastScores();
}

void UScreenGameplayHud::NativeDestruct()
{
	Super::NativeDestruct();

	AGameStateGameplay* const GameState = Cast<AGameStateGameplay>(UGameplayStatics::GetGameState(GetWorld()));
	if (GameState)
	{
		GameState->UpdateScoresEvent.Remove(OnUpdateScoresHandle);
	}
}

void UScreenGameplayHud::OnUpdateScores(TArray<int> const& Scores) const
{
	FNumberFormattingOptions Format = FNumberFormattingOptions();
	Format.SetMinimumIntegralDigits(2);
	TextScoreHome->SetText(FText::AsNumber(Scores[static_cast<int>(ETeam::Home)], &Format));
	TextScoreAway1->SetText(FText::AsNumber(Scores[static_cast<int>(ETeam::Away1)], &Format));
	TextScoreAway2->SetText(FText::AsNumber(Scores[static_cast<int>(ETeam::Away2)], &Format));
}
