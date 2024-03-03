// Copyright 2024 Impending Technologies

#include "UI/Menu/ScreenTeamSelect.h"

#include "Actor/Menu/GameStateMenu.h"
#include "Algo/Count.h"
#include "Subsystem/TeamDataSubsystem.h"
#include "UI/Menu/PartTeam.h"

void UScreenTeamSelect::NativeOnInitialized()
{
	static UPartTeam const* const PartTeam[8] = {Team1, Team2, Team3, Team4, Team5, Team6, Team7, Team8};

	Super::NativeOnInitialized();

	UTeamDataSubsystem const* const TeamDataSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UTeamDataSubsystem>();
	TArray<UTeamData const*> const TeamData = TeamDataSubsystem->Choose(8, UTeamDataSubsystem::EChooseMode::Sorted);

	int const Max = std::min(std::size(PartTeam), static_cast<size_t>(TeamData.Num()));
	for (int i = 0; i < Max; ++i)
	{
		PartTeam[i]->SetLogo(TeamData[i]);
		Teams.Emplace(FLeagueTeam(TeamData[i], ELeagueController::CPU));
	}

	TrackedSlotIndex = 0;
}


void UScreenTeamSelect::OnInputMain(int const PlayerIndex)
{
	Super::OnInputMain(PlayerIndex);

	Teams[TrackedSlotIndex].Controller = ELeagueController::Human;
	++TrackedSlotIndex;

	AGameStateMenu const* const GameState = GetWorld()->GetGameState<AGameStateMenu>();
	check(GameState);

	uint HumanTeams = Algo::CountIf(Teams, [](FLeagueTeam const& LeagueTeam) {return LeagueTeam.Controller == ELeagueController::Human;});
	if (HumanTeams == GameState->GetExpectedHumans())
	{
		ULeagueSubsystem* const LeagueSubsystem = GetGameInstance()->GetSubsystem<ULeagueSubsystem>();
		LeagueSubsystem->InitializeLeague(Teams);
		ScreenManager->NavigateTo("PlayerSelect");
	}
}

void UScreenTeamSelect::OnInputBack(int const PlayerIndex)
{
	ScreenManager->NavigateTo("Humans");
}
