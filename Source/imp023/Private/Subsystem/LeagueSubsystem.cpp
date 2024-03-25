// Copyright 2024 Impending Technologies


#include "Subsystem/LeagueSubsystem.h"

#include "Algo/RandomShuffle.h"
#include "Data/TeamData.h"

bool FLeagueTeam::operator==(uint32 const ID) const
{
	return Team->ID == ID;
}

int FLeagueTeam::Points() const
{
	return Wins * 4 + SharedWins * 3 + Draws * 2 + SharedLosses;
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

					Match.Emplace(&LeagueTeams[a], ETeam::Home);
					Match.Emplace(&LeagueTeams[b], ETeam::Away1);
					Match.Emplace(&LeagueTeams[c], ETeam::Away2);

					Schedule.Add(Match);
				}
			}
		}
	}
	Algo::RandomShuffle(Schedule);
}

TArray<FLeagueTeamForMatch> const& ULeagueSubsystem::CurrentMatchTeams() const
{
	return Schedule[GameIndex];
}

bool RankedSort(FLeagueTeam const& A, FLeagueTeam const& B)
{
	int const PointsA = A.Points();
	int const PointsB = B.Points();
	if (PointsA > PointsB)
	{
		return true;
	}
	if (PointsA < PointsB)
	{
		return false;
	}
	return A.Games < B.Games;
}

void ULeagueSubsystem::MatchComplete(TArray<int> const& Scores)
{
	TArray<FLeagueTeamForMatch> const& Teams = CurrentMatchTeams();

	int Points[3] = {0, 0, 0};
	for (int i = 0; i < 3; ++i)
	{
		Points[i] += Scores[i] > Scores[(i + 1) % 3] ? 2 : 0;
		Points[i] += Scores[i] == Scores[(i + 1) % 3] ? 1 : 0;
		Points[i] += Scores[i] > Scores[(i + 2) % 3] ? 2 : 0;
		Points[i] += Scores[i] == Scores[(i + 2) % 3] ? 1 : 0;
	}

	for (int i = 0; i < 3; ++i)
	{
		FLeagueTeam* const Team = Teams[i].LeagueTeam;
		++Team->Games;
		switch (Points[i])
		{
			case 0:
				++Team->Losses;
				break;
			case 1:
				++Team->SharedLosses;
				break;
			case 2:
				++Team->Draws;
				break;
			case 3:
				++Team->SharedWins;
				break;
			case 4:
				++Team->Wins;
				break;
			default:
				break;
		}
	}

	LeagueTeams.StableSort(&RankedSort);

	++GameIndex;
}

FLeagueTeam const* ULeagueSubsystem::GetTeamByID(uint32 const ID) const
{
	return LeagueTeams.FindByKey(ID);
}

FLeagueTeam const* ULeagueSubsystem::GetTeamByIndex(uint32 const Index) const
{
	return &LeagueTeams[Index];
}

FTextFormat const& OrdinalFormat(int const Num, bool const Tied)
{
	static FTextFormat const St(INVTEXT("{0}st"));
	static FTextFormat const Nd(INVTEXT("{0}nd"));
	static FTextFormat const Rd(INVTEXT("{0}rd"));
	static FTextFormat const Th(INVTEXT("{0}th"));
	static FTextFormat const TSt(INVTEXT("T-{0}st"));
	static FTextFormat const TNd(INVTEXT("T-{0}nd"));
	static FTextFormat const TRd(INVTEXT("T-{0}rd"));
	static FTextFormat const TTh(INVTEXT("T-{0}th"));

	switch (Num % 100)
	{
		case 11:
		case 12:
		case 13:
			return Tied ? TTh : Th;
		default:
			break;
	}
	switch (Num % 10)
	{
		case 1:
			return Tied ? TSt : St;
		case 2:
			return Tied ? TNd : Nd;
		case 3:
			return Tied ? TRd : Rd;;
		default:
			break;
	}
	return Tied ? TTh : Th;
}

FText OrdinalText(int const Num, bool const Tied)
{
	return FText::Format(OrdinalFormat(Num, Tied), Num);
}

FText ULeagueSubsystem::GetTeamRankByID(uint32 const ID) const
{
	int const Index = LeagueTeams.IndexOfByKey(ID);
	return GetTeamRankByIndex(Index);
}

FText ULeagueSubsystem::GetTeamRankByIndex(uint32 const Index) const
{
	int CheckIndex = Index;
	while (CheckIndex > 0 && LeagueTeams[CheckIndex - 1].Points() == LeagueTeams[CheckIndex].Points())
	{
		--CheckIndex;
	}
	bool const Tied = CheckIndex != Index || (Index != (LeagueTeams.Num() - 1) && LeagueTeams[Index].Points() == LeagueTeams[Index + 1].Points());
	return OrdinalText(CheckIndex + 1, Tied);
}
