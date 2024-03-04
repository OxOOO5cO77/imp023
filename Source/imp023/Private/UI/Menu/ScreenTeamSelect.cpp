// Copyright 2024 Impending Technologies

#include "UI/Menu/ScreenTeamSelect.h"

#include "Actor/Menu/GameStateMenu.h"
#include "Algo/Count.h"
#include "Data/TeamData.h"
#include "Subsystem/TeamDataSubsystem.h"
#include "UI/Menu/PartTeam.h"

static constexpr int GTeamCount = 8;

void UScreenTeamSelect::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	UTeamDataSubsystem const* const TeamDataSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UTeamDataSubsystem>();
	TArray<UTeamData const*> const TeamData = TeamDataSubsystem->Choose(GTeamCount, UTeamDataSubsystem::EChooseMode::Sorted);

	int const Max = std::min(GTeamCount, TeamData.Num());
	for (int i = 0; i < Max; ++i)
	{
		Part(i)->SetLogo(TeamData[i]);
		Teams.Emplace(FLeagueTeam(TeamData[i], ELeagueController::CPU));
	}

	TrackedSlotIndex = 0;
	Part(0)->SetSelectedColor(TeamData[0]->Color);
}


void UScreenTeamSelect::OnInputMain(int const PlayerIndex)
{
	Super::OnInputMain(PlayerIndex);

	Teams[TrackedSlotIndex].Controller = ELeagueController::Human;
	Part(TrackedSlotIndex)->SetText("Human");

	NextTrackedIndex();;

	AGameStateMenu const* const GameState = GetWorld()->GetGameState<AGameStateMenu>();
	check(GameState);

	uint HumanTeams = Algo::CountIf(Teams, [](FLeagueTeam const& LeagueTeam) { return LeagueTeam.Controller == ELeagueController::Human; });
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

void UScreenTeamSelect::OnInputUp(int const PlayerIndex)
{
	PrevTrackedIndex();
}

void UScreenTeamSelect::OnInputDown(int const PlayerIndex)
{
	NextTrackedIndex();
}

UPartTeam const* UScreenTeamSelect::Part(uint const Index) const
{
	static UPartTeam const* const PartTeam[GTeamCount] = {Team1, Team2, Team3, Team4, Team5, Team6, Team7, Team8};
	return PartTeam[Index];
}

void UScreenTeamSelect::NextTrackedIndex()
{
	Part(TrackedSlotIndex)->SetSelectedColor(FLinearColor::White);

	do
	{
		TrackedSlotIndex = (TrackedSlotIndex + 1) % GTeamCount;
	}
	while( Teams[TrackedSlotIndex].Controller == ELeagueController::Human);
	Part(TrackedSlotIndex)->SetSelectedColor(Teams[TrackedSlotIndex].Team->Color);
}

void UScreenTeamSelect::PrevTrackedIndex()
{
	Part(TrackedSlotIndex)->SetSelectedColor(FLinearColor::White);
	do
	{
		TrackedSlotIndex = (TrackedSlotIndex + GTeamCount - 1) % GTeamCount;
	}
	while( Teams[TrackedSlotIndex].Controller == ELeagueController::Human);
	Part(TrackedSlotIndex)->SetSelectedColor(Teams[TrackedSlotIndex].Team->Color);
}
