// Copyright 2024 Impending Technologies

#include "UI/Gameplay/UI_GameplayHud.h"

#include "Actor/Game/GameStateGameplay.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

bool UUI_GameplayHud::Initialize()
{
	bool const BaseInit = Super::Initialize();

	AGameStateGameplay* const GameState = Cast<AGameStateGameplay>(UGameplayStatics::GetGameState(GetWorld()));
	if (GameState)
	{
		GameState->OnUpdateScores().AddUObject(this, &UUI_GameplayHud::OnUpdateScores);
	}

	return BaseInit;
}

void UUI_GameplayHud::OnUpdateScores(TArray<int> const& Scores) const
{
	FNumberFormattingOptions Format = FNumberFormattingOptions();
	Format.SetMinimumIntegralDigits(2);
	TextScoreHome->SetText(FText::AsNumber(Scores[static_cast<int>(ETeam::Home)], &Format));
	TextScoreAway1->SetText(FText::AsNumber(Scores[static_cast<int>(ETeam::Away1)], &Format));
	TextScoreAway2->SetText(FText::AsNumber(Scores[static_cast<int>(ETeam::Away2)], &Format));
}
