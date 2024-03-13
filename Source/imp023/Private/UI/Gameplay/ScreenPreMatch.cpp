// Copyright 2024 Impending Technologies
#include "UI/Gameplay/ScreenPreMatch.h"

#include "Actor/Gameplay/GameStateGameplay.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Data/TeamData.h"
#include "Subsystem/LeagueSubsystem.h"
#include "Subsystem/TeamStateSubsystem.h"

void UScreenPreMatch::NativeOnInitialized()
{
	Super::NativeOnInitialized();

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

	TTuple<int,int,int> const& RecordHome = LeagueSubsystem->GetWinLoseDraw(Home->ID);
	TTuple<int,int,int> const& RecordAway1 = LeagueSubsystem->GetWinLoseDraw(Away1->ID);
	TTuple<int,int,int> const& RecordAway2 = LeagueSubsystem->GetWinLoseDraw(Away2->ID);


	TextHome->SetText(FText::Format(INVTEXT("({0}-{1}-{2})"), RecordHome.Get<0>(), RecordHome.Get<1>(), RecordHome.Get<2>()));
	TextAway1->SetText(FText::Format(INVTEXT("({0}-{1}-{2})"), RecordAway1.Get<0>(), RecordAway1.Get<1>(), RecordAway1.Get<2>()));
	TextAway2->SetText(FText::Format(INVTEXT("({0}-{1}-{2})"), RecordAway2.Get<0>(), RecordAway2.Get<1>(), RecordAway2.Get<2>()));

}

void UScreenPreMatch::OnInputMain(int const PlayerIndex)
{
	Super::OnInputMain(PlayerIndex);

	AGameStateGameplay* GameState = GetWorld()->GetGameState<AGameStateGameplay>();

	GameState->SetState(EGameplayGameState::PrePeriod);
}
