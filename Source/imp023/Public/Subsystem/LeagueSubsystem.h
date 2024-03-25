// Copyright 2024 Impending Technologies

#pragma once

#include "CoreMinimal.h"
#include "Enum/ETeam.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "LeagueSubsystem.generated.h"


class UTeamData;

enum class ELeagueController
{
	CPU,
	Human,
};

struct FLeagueTeam
{
	FLeagueTeam(UTeamData const* const InTeam, ELeagueController const InController)
		: Team(InTeam)
		, Controller(InController)
		, Games(0)
		, Wins(0)
		, SharedWins(0)
		, Draws(0)
		, SharedLosses(0)
		, Losses(0)
	{
	}

	bool operator==(uint32 const ID) const;

	int Points() const;

	UTeamData const* const Team;
	ELeagueController Controller;
	int Games;
	int Wins;
	int SharedWins;
	int Draws;
	int SharedLosses;
	int Losses;
};

struct FLeagueTeamForMatch
{
	FLeagueTeamForMatch(FLeagueTeam* const InTeam, ETeam const InHomeAway)
		: LeagueTeam(InTeam)
		, HomeAway(InHomeAway)
	{
	}

	FLeagueTeam* const LeagueTeam;
	ETeam const HomeAway;
};

/**
 *
 */
UCLASS()
class IMP023_API ULeagueSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	void InitializeLeague(TArray<FLeagueTeam> const& Teams);

	TArray<FLeagueTeamForMatch> const& CurrentMatchTeams() const;
	void MatchComplete(TArray<int> const& Scores);

	FLeagueTeam const* GetTeamByID(uint32 const ID) const;
	FLeagueTeam const* GetTeamByIndex(uint32 Index) const;

	FText GetTeamRankByID(uint32 const ID) const;
	FText GetTeamRankByIndex(uint32 Index) const;

	static constexpr int GTeamCount = 8;

private:
	TArray<FLeagueTeam> LeagueTeams;
	int GameIndex;
	TArray<TArray<FLeagueTeamForMatch>> Schedule;
};
