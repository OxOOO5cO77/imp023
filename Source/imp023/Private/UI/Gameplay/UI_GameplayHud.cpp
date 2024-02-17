// Copyright 2024 Impending Technologies

#include "UI/Gameplay/UI_GameplayHud.h"

#include "Actor/Gameplay/GameStateGameplay.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void UUI_GameplayHud::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	AGameStateGameplay* const GameState = Cast<AGameStateGameplay>(UGameplayStatics::GetGameState(GetWorld()));
	if (GameState)
	{
		OnUpdateScoresHandle = GameState->OnUpdateScores().AddUObject(this, &UUI_GameplayHud::OnUpdateScores);
	}
}

void UUI_GameplayHud::NativeDestruct()
{
	Super::NativeDestruct();

	AGameStateGameplay* const GameState = Cast<AGameStateGameplay>(UGameplayStatics::GetGameState(GetWorld()));
	if (GameState)
	{
		GameState->OnUpdateScores().Remove(OnUpdateScoresHandle);
	}
}

void UUI_GameplayHud::OnUpdateScores(TArray<int> const& Scores) const
{
	FNumberFormattingOptions Format = FNumberFormattingOptions();
	Format.SetMinimumIntegralDigits(2);
	TextScoreHome->SetText(FText::AsNumber(Scores[static_cast<int>(ETeam::Home)], &Format));
	TextScoreAway1->SetText(FText::AsNumber(Scores[static_cast<int>(ETeam::Away1)], &Format));
	TextScoreAway2->SetText(FText::AsNumber(Scores[static_cast<int>(ETeam::Away2)], &Format));
}
