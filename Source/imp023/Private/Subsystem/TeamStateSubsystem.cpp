// Copyright 2024 Impending Technologies


#include "Subsystem/TeamStateSubsystem.h"

#include "Data/TeamData.h"
#include "Subsystem/TeamDataSubsystem.h"

void UTeamStateSubsystem::InitializeTeams()
{
	UGameInstance* const GameInstance = GetWorld()->GetGameInstance();
	UTeamDataSubsystem* const TeamDataSubsystem = GameInstance->GetSubsystem<UTeamDataSubsystem>();
	check(TeamDataSubsystem);

	TArray<UTeamData*> TeamData = TeamDataSubsystem->ChooseThree();

	TeamMap.Emplace(ETeam::Home, TeamData[0]);
	TeamMap.Emplace(ETeam::Away1, TeamData[1]);
	TeamMap.Emplace(ETeam::Away2, TeamData[2]);
}

UTexture2D* UTeamStateSubsystem::GetLogo(UObject* const Outer, ETeam const Team) const
{
	UTeamData const* TeamData = TeamMap[Team];
	check(TeamData);
	return TeamData->Logo.LoadSynchronous();
}

FLinearColor UTeamStateSubsystem::GetColor(ETeam const Team) const
{
	UTeamData const* TeamData = TeamMap[Team];
	check(TeamData);
	return TeamData->Color;
}

FString UTeamStateSubsystem::GetAbbrev(ETeam Team) const
{
	UTeamData const* TeamData = TeamMap[Team];
	check(TeamData);
	return TeamData->Abbrev;
}

UPlayerData const* UTeamStateSubsystem::GetTeamPlayer(ETeam const Team, EPlayerPosition const PlayerPosition) const
{
	UTeamData const* TeamData = TeamMap[Team];
	return TeamData->PlayerByPosition(PlayerPosition);
}
