// Copyright 2024 Impending Technologies

#include "UI/Menu/ScreenPlayerSelect.h"

#include "Actor/Menu/GameStateMenu.h"
#include "Subsystem/LeagueSubsystem.h"
#include "Subsystem/TeamStateSubsystem.h"
#include "UI/Menu/PartTeam.h"

static constexpr int GMaxSlot = 2;

void UScreenPlayerSelect::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	ULeagueSubsystem const* const LeagueSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<ULeagueSubsystem>();
	check(LeagueSubsystem);

	MatchTeams = LeagueSubsystem->NextMatchTeams();

	for (int i = 0; i < 3; ++i)
	{
		UPartTeam* const PartTeam = Part(i);
		PartTeam->SetLogo(MatchTeams[i].Team);
		PartTeam->SetText(MatchTeams[i].Controller == ELeagueController::Human ? FString() : TEXT("CPU"));;
	}

	UTeamStateSubsystem* const TeamStateSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UTeamStateSubsystem>();
	check(TeamStateSubsystem);

	TeamStateSubsystem->InitializeTeams(MatchTeams);

	TrackedSlotIndex = 0;
	NextTrackedIndex();

	if (TrackedSlotIndex < 3)
	{
		Part(TrackedSlotIndex)->SetText(TEXT("PRESS START"));
	}
}

UPartTeam* UScreenPlayerSelect::Part(uint32 const PartIndex) const
{
	static UPartTeam* const Parts[3] = {TeamHome, TeamAway1, TeamAway2};
	return Parts[PartIndex];
}

void UScreenPlayerSelect::NextTrackedIndex()
{
	while (TrackedSlotIndex <= GMaxSlot && MatchTeams[TrackedSlotIndex].Controller == ELeagueController::CPU)
	{
		++TrackedSlotIndex;
	}
}

void UScreenPlayerSelect::PrevTrackedIndex()
{
	while (TrackedSlotIndex > 0 && MatchTeams[TrackedSlotIndex - 1].Controller == ELeagueController::CPU)
	{
		--TrackedSlotIndex;
	}
}


void UScreenPlayerSelect::OnInputMain(int const PlayerIndex)
{
	Super::OnInputMain(PlayerIndex);

	if (TrackedSlotIndex > GMaxSlot)
	{
		GetWorld()->ServerTravel("/Game/Level/Arena");
		return;
	}

	AGameStateMenu* const GameState = GetWorld()->GetGameState<AGameStateMenu>();
	check(GameState);

	bool const Success = GameState->SetPlayerToTeam(PlayerIndex, MatchTeams[TrackedSlotIndex].HomeAway);

	if (Success)
	{
		Part(TrackedSlotIndex)->SetText(FString::Printf(TEXT("PLAYER %d"), PlayerIndex));

		++TrackedSlotIndex;
		NextTrackedIndex();

		if (TrackedSlotIndex <= GMaxSlot)
		{
			Part(TrackedSlotIndex)->SetText(TEXT("PRESS START"));;
		}
	}
}


void UScreenPlayerSelect::OnInputBack(int const PlayerIndex)
{
	if (TrackedSlotIndex == 0)
	{
		return;
	}

	if (TrackedSlotIndex <= GMaxSlot)
	{
		Part(TrackedSlotIndex)->SetText(FString());
	}

	PrevTrackedIndex();

	AGameStateMenu* const GameState = GetWorld()->GetGameState<AGameStateMenu>();
	check(GameState);

	GameState->DisassociateTeam(MatchTeams[TrackedSlotIndex].HomeAway);

	Part(TrackedSlotIndex)->SetText(TEXT("PRESS START"));;
}
