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
	{
	}

	UTeamData const* const Team;
	ELeagueController Controller;
};

struct FLeagueTeamForMatch : public FLeagueTeam
{
	FLeagueTeamForMatch(UTeamData const* const InTeam, ELeagueController const InController, ETeam const InHomeAway)
		: FLeagueTeam(InTeam, InController)
		  , HomeAway(InHomeAway)
	{
	}

	ETeam HomeAway;
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

	TArray<FLeagueTeamForMatch> NextMatchTeams() const;

private:
	TArray<FLeagueTeam> LeagueTeams;
};
