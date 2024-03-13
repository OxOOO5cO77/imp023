// Copyright 2024 Impending Technologies


#include "UI/Gameplay/ScreenPrePeriod.h"

#include "Actor/Gameplay/GameStateGameplay.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Data/TeamData.h"
#include "Subsystem/TeamStateSubsystem.h"

void UScreenPrePeriod::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	AGameStateGameplay const* const GameState = GetWorld()->GetGameState<AGameStateGameplay>();

	TextPeriod->SetText(FText::Format(INVTEXT("Period {0}"), GameState->Period));

	UTeamStateSubsystem const* const TeamStateSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UTeamStateSubsystem>();
	check(TeamStateSubsystem);

	UTeamData const* const Home = TeamStateSubsystem->GetTeam(ETeam::Home);
	UTeamData const* const Away1 = TeamStateSubsystem->GetTeam(ETeam::Away1);
	UTeamData const* const Away2 = TeamStateSubsystem->GetTeam(ETeam::Away2);

	ImageHome->SetBrushFromTexture(Home->Logo.LoadSynchronous());
	ImageAway1->SetBrushFromTexture(Away1->Logo.LoadSynchronous());
	ImageAway2->SetBrushFromTexture(Away2->Logo.LoadSynchronous());
}

void UScreenPrePeriod::OnInputMain(int const PlayerIndex)
{
	Super::OnInputMain(PlayerIndex);

	AGameStateGameplay* const GameState = GetWorld()->GetGameState<AGameStateGameplay>();
	GameState->SetState(EGameplayGameState::PrePlay);
}
