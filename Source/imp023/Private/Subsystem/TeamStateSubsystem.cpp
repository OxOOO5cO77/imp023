// Copyright 2024 Impending Technologies


#include "Subsystem/TeamStateSubsystem.h"

#include "Kismet/GameplayStatics.h"
#include "Subsystem/TeamDataSubsystem.h"

void UTeamStateSubsystem::InitializeTeams()
{
	UGameInstance* const GameInstance = UGameplayStatics::GetGameInstance(this);
	UTeamDataSubsystem* const TeamDataSubsystem = GameInstance->GetSubsystem<UTeamDataSubsystem>();
	check(TeamDataSubsystem);

	TArray<FTeamData> TeamData = TeamDataSubsystem->ChooseThree();
	TeamMap.Emplace(ETeam::Home, TeamData[0]);
	TeamMap.Emplace(ETeam::Away1, TeamData[1]);
	TeamMap.Emplace(ETeam::Away2, TeamData[2]);
}

UTexture2D* UTeamStateSubsystem::GetLogo(UObject* const Outer, ETeam const Team) const
{
	FTeamData const& TeamData = TeamMap[Team];
	FString const FullPath = "/Game/Team/" + TeamData.AssetPath + "/Logo";;
	UTexture2D* Asset = LoadObject<UTexture2D>(Outer, *FullPath);
	return Asset;
}

FLinearColor UTeamStateSubsystem::GetColor(ETeam const Team) const
{
	FTeamData const& TeamData = TeamMap[Team];
	return TeamData.Color;
}

FPlayerData const* UTeamStateSubsystem::GetTeamPlayer(ETeam const Team, EPlayerPosition const PlayerPosition) const
{
	FTeamData const& TeamData = TeamMap[Team];
	return TeamData.PlayerByPosition(PlayerPosition);
}
