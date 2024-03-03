// Copyright 2024 Impending Technologies


#include "Subsystem/TeamStateSubsystem.h"

#include "Data/TeamData.h"
#include "Subsystem/LeagueSubsystem.h"

void UTeamStateSubsystem::InitializeTeams(TArray<FLeagueTeamForMatch> const& TeamData)
{
	check(TeamData.Num() == 3);

	TeamMap.Emplace(ETeam::Home, TeamData[0].Team);
	TeamMap.Emplace(ETeam::Away1, TeamData[1].Team);
	TeamMap.Emplace(ETeam::Away2, TeamData[2].Team);
}

UTexture2D* UTeamStateSubsystem::GetLogo(UObject* const Outer, ETeam const Team) const
{
	UTeamData const* const TeamData = TeamMap[Team];
	check(TeamData);
	return TeamData->Logo.LoadSynchronous();
}

FLinearColor UTeamStateSubsystem::GetColor(ETeam const Team) const
{
	UTeamData const* const TeamData = TeamMap[Team];
	check(TeamData);
	return TeamData->Color;
}

FString UTeamStateSubsystem::GetAbbrev(ETeam Team) const
{
	UTeamData const* const TeamData = TeamMap[Team];
	check(TeamData);
	return TeamData->Abbrev;
}

UPlayerData const* UTeamStateSubsystem::GetTeamPlayer(ETeam const Team, EPlayerPosition const PlayerPosition) const
{
	UTeamData const* const TeamData = TeamMap[Team];
	return TeamData->PlayerByPosition(PlayerPosition);
}
