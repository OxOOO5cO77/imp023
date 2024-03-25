// Copyright 2024 Impending Technologies

#include "UI/Menu/ScreenStandings.h"

#include "Subsystem/LeagueSubsystem.h"
#include "UI/Manager/ScreenManager.h"
#include "UI/Menu/PartStanding.h"

void UScreenStandings::NativeConstruct()
{
	Super::NativeConstruct();

	ULeagueSubsystem const* const LeagueSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<ULeagueSubsystem>();

	for(int i=0; i<ULeagueSubsystem::GTeamCount; ++i)
	{
		UPartStanding const* const PartStanding = Part(i);
		FLeagueTeam const* const LeagueTeam = LeagueSubsystem->GetTeamByIndex(i);
		FText RankText = LeagueSubsystem->GetTeamRankByIndex(i);
		PartStanding->Setup(LeagueTeam, RankText);
	}
}

void UScreenStandings::OnInputMain(int const PlayerIndex)
{
	Super::OnInputMain(PlayerIndex);

	ScreenManager->NavigateTo("PlayerSelect");
}

UPartStanding const* UScreenStandings::Part(uint32 const Index) const
{
	UPartStanding const* const PartTeam[ULeagueSubsystem::GTeamCount] = {Team1st, Team2nd, Team3rd, Team4th, Team5th, Team6th, Team7th, Team8th};
	return PartTeam[Index];
}
