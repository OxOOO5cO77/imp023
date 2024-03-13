// Copyright 2024 Impending Technologies


#include "Subsystem/LeagueSubsystem.h"

#include "Data/TeamData.h"

bool FLeagueTeam::operator==(uint32 const ID) const
{
	return Team->ID == ID;
}

void ULeagueSubsystem::InitializeLeague(TArray<FLeagueTeam> const& Teams)
{
	LeagueTeams = Teams;

	for (int a = 0; a < Teams.Num(); ++a)
	{
		for (int b = 0; b < Teams.Num(); ++b)
		{
			for (int c = 0; c < Teams.Num(); ++c)
			{
				if (a != b && a != c && b != c)
				{
					TArray<FLeagueTeamForMatch> Match;

					Match.Emplace(Teams[a].Team, Teams[a].Controller, ETeam::Home);
					Match.Emplace(Teams[b].Team, Teams[b].Controller, ETeam::Away1);
					Match.Emplace(Teams[c].Team, Teams[c].Controller, ETeam::Away2);

					Schedule.Add(Match);
				}
			}
		}
	}
}

TArray<FLeagueTeamForMatch> const& ULeagueSubsystem::NextMatchTeams() const
{
	return Schedule[DayIndex];
}

void ULeagueSubsystem::MatchComplete()
{
	DayIndex = (DayIndex + 1) % Schedule.Num();
}

TTuple<int, int, int> ULeagueSubsystem::GetWinLoseDraw(uint32 const ID) const
{
	FLeagueTeam const* const LeagueTeam = LeagueTeams.FindByKey(ID);
	return MakeTuple(LeagueTeam->Win, LeagueTeam->Lose, LeagueTeam->Draw);
}
