// Copyright 2024 Impending Technologies


#include "Subsystem/TeamStateSubsystem.h"

#include "Subsystem/LeagueSubsystem.h"

void UTeamStateSubsystem::InitializeTeams(TArray<FLeagueTeamForMatch> const& TeamData)
{
	check(TeamData.Num() == 3);

	TeamMap.Emplace(ETeam::Home, TeamData[0].LeagueTeam->Team);
	TeamMap.Emplace(ETeam::Away1, TeamData[1].LeagueTeam->Team);
	TeamMap.Emplace(ETeam::Away2, TeamData[2].LeagueTeam->Team);
}

UTeamData const* UTeamStateSubsystem::GetTeam(ETeam const Team) const
{
	return TeamMap[Team];
}
