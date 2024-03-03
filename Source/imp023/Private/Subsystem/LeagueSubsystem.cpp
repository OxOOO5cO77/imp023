// Copyright 2024 Impending Technologies


#include "Subsystem/LeagueSubsystem.h"

void ULeagueSubsystem::InitializeLeague(TArray<FLeagueTeam> const& Teams)
{
	LeagueTeams = Teams;
}

TArray<FLeagueTeamForMatch> ULeagueSubsystem::NextMatchTeams() const
{
	TArray<FLeagueTeamForMatch> Result;

	Result.Emplace(LeagueTeams[0].Team, LeagueTeams[0].Controller, ETeam::Home);
	Result.Emplace(LeagueTeams[1].Team, LeagueTeams[1].Controller, ETeam::Away1);
	Result.Emplace(LeagueTeams[2].Team, LeagueTeams[2].Controller, ETeam::Away2);

	return Result;
}
