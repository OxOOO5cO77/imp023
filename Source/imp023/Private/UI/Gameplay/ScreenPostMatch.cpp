// Copyright 2024 Impending Technologies
#include "UI/Gameplay/ScreenPostMatch.h"

#include "Actor/Gameplay/GameStateGameplay.h"
#include "Subsystem/LeagueSubsystem.h"
#include "Subsystem/MenuTransitionSubsystem.h"

void UScreenPostMatch::OnInputMain(int const ControllerIndex)
{
	Super::OnInputMain(ControllerIndex);

	ULeagueSubsystem* const LeagueSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<ULeagueSubsystem>();
	check(LeagueSubsystem);

	AGameStateGameplay const* const GameStateGameplay = GetWorld()->GetGameState<AGameStateGameplay>();

	LeagueSubsystem->MatchComplete(GameStateGameplay->Score);

	UMenuTransitionSubsystem* const MenuTransitionSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UMenuTransitionSubsystem>();
	MenuTransitionSubsystem->SetStartScreen("Standings");;

	GetWorld()->ServerTravel("/Game/Level/MainMenu");
}
