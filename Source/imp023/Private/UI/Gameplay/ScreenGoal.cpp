// Copyright 2024 Impending Technologies


#include "UI/Gameplay/ScreenGoal.h"

#include "Actor/Gameplay/GameStateGameplay.h"
#include "Components/HorizontalBox.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

#include "Data/PlayerData.h"
#include "Subsystem/TeamStateSubsystem.h"

class UTeamStateSubsystem;

void UScreenGoal::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	AGameStateGameplay const* GameState = CastChecked<AGameStateGameplay>(GetWorld()->GetGameState());
	UTeamStateSubsystem* const TeamStateSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UTeamStateSubsystem>();
	check(TeamStateSubsystem);

	auto const& [GoalPlayer, GoalTeam, OwnGoalPlayer, OwnGoalTeam, TimeOfGoal] = GameState->GetLastGoal();

	BoxGoal->SetVisibility(GoalPlayer != nullptr ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	if (GoalPlayer != nullptr)
	{
		TextGoalPlayer->SetText(FText::FromString(GoalPlayer->Name));
		TextGoalTeam->SetText(FText::FromString(TeamStateSubsystem->GetAbbrev(GoalTeam)));
	}

	BoxOwnGoal->SetVisibility(OwnGoalPlayer != nullptr ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	if (OwnGoalPlayer != nullptr)
	{
		TextOwnGoalPlayer->SetText(FText::FromString(OwnGoalPlayer->Name));
		TextOwnGoalTeam->SetText(FText::FromString(TeamStateSubsystem->GetAbbrev(OwnGoalTeam)));
	}

	TextTimeOfGoal->SetText(FText::FormatOrdered(INVTEXT("{0}s"), TimeOfGoal));

	UPlayerData const* PlayerToUse = GoalPlayer != nullptr ? GoalPlayer : OwnGoalPlayer;
	ImageGoalPlayer->SetBrushFromTexture(PlayerToUse->Image.LoadSynchronous());
}
