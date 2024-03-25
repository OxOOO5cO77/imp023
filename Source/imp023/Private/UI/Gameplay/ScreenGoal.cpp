// Copyright 2024 Impending Technologies


#include "UI/Gameplay/ScreenGoal.h"

#include "Actor/Gameplay/GameStateGameplay.h"
#include "Components/HorizontalBox.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

#include "Data/PlayerData.h"
#include "Data/TeamData.h"
#include "Subsystem/TeamStateSubsystem.h"

class UTeamStateSubsystem;

void UScreenGoal::NativeConstruct()
{
	Super::NativeConstruct();

	AGameStateGameplay const* GameState = GetWorld()->GetGameState<AGameStateGameplay>();
	UTeamStateSubsystem* const TeamStateSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UTeamStateSubsystem>();
	check(TeamStateSubsystem);

	auto const& [GoalPlayer, GoalTeam, OwnGoalPlayer, OwnGoalTeam, TimeOfGoal] = GameState->GetLastGoal();

	BoxGoal->SetVisibility(GoalPlayer != nullptr ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	if (GoalPlayer != nullptr)
	{
		TextGoalPlayer->SetText(FText::FromString(GoalPlayer->Name));
		UTeamData const* const TeamData = TeamStateSubsystem->GetTeam(GoalTeam);
		TextGoalTeam->SetText(FText::FromString(TeamData->Abbrev));
	}

	BoxOwnGoal->SetVisibility(OwnGoalPlayer != nullptr ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	if (OwnGoalPlayer != nullptr)
	{
		TextOwnGoalPlayer->SetText(FText::FromString(OwnGoalPlayer->Name));
		UTeamData const* const TeamData = TeamStateSubsystem->GetTeam(GoalTeam);
		TextOwnGoalTeam->SetText(FText::FromString(TeamData->Abbrev));
	}

	TextTimeOfGoal->SetText(FText::FormatOrdered(INVTEXT("{0}s"), TimeOfGoal));

	UPlayerData const* PlayerToUse = GoalPlayer != nullptr ? GoalPlayer : OwnGoalPlayer;
	ImageGoalPlayer->SetBrushFromTexture(PlayerToUse->Image.LoadSynchronous());
}

void UScreenGoal::OnInputMain(int const PlayerIndex)
{
	Super::OnInputMain(PlayerIndex);

	AGameStateGameplay* const GameState = GetWorld()->GetGameState<AGameStateGameplay>();
	GameState->SetState(EGameplayGameState::PrePlay);
}
