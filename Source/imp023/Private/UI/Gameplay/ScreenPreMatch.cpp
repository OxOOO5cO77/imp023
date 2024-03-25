// Copyright 2024 Impending Technologies
#include "UI/Gameplay/ScreenPreMatch.h"

#include "Actor/Gameplay/GameStateGameplay.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Data/TeamData.h"
#include "Subsystem/LeagueSubsystem.h"
#include "Subsystem/TeamStateSubsystem.h"

void UScreenPreMatch::NativeConstruct()
{
	Super::NativeConstruct();

	AGameStateGameplay const* const GameState = GetWorld()->GetGameState<AGameStateGameplay>();

	UTeamStateSubsystem const* const TeamStateSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UTeamStateSubsystem>();
	check(TeamStateSubsystem);

	UTeamData const* const Home = TeamStateSubsystem->GetTeam(ETeam::Home);
	UTeamData const* const Away1 = TeamStateSubsystem->GetTeam(ETeam::Away1);
	UTeamData const* const Away2 = TeamStateSubsystem->GetTeam(ETeam::Away2);

	ImageHome->SetBrushFromTexture(Home->Logo.LoadSynchronous());
	ImageAway1->SetBrushFromTexture(Away1->Logo.LoadSynchronous());
	ImageAway2->SetBrushFromTexture(Away2->Logo.LoadSynchronous());

	ULeagueSubsystem const* const LeagueSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<ULeagueSubsystem>();
	check(LeagueSubsystem);

	FText RankHome = LeagueSubsystem->GetTeamRankByID(Home->ID);
	FText RankAway1 = LeagueSubsystem->GetTeamRankByID(Away1->ID);
	FText RankAway2 = LeagueSubsystem->GetTeamRankByID(Away2->ID);

	TextHome->SetText(RankHome);
	TextAway1->SetText(RankAway1);
	TextAway2->SetText(RankAway2);
}


void UScreenPreMatch::OnInputMain(int const PlayerIndex)
{
	Super::OnInputMain(PlayerIndex);

	AGameStateGameplay* GameState = GetWorld()->GetGameState<AGameStateGameplay>();

	GameState->SetState(EGameplayGameState::PrePeriod);
}
