// Copyright 2024 Impending Technologies

#pragma once

#include "CoreMinimal.h"
#include "Enum/ETeam.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "TeamStateSubsystem.generated.h"

struct FLeagueTeamForMatch;
class UTeamData;
/**
 *
 */
UCLASS()
class IMP023_API UTeamStateSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	void InitializeTeams(TArray<FLeagueTeamForMatch> const& TeamData);

	UTeamData const* GetTeam(ETeam const Team) const;

private:
	TMap<ETeam,UTeamData const*> TeamMap;
};
