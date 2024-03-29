// Copyright 2024 Impending Technologies

#include "Actor/Menu/GameStateMenu.h"

#include "Actor/Menu/PlayerStateMenu.h"
#include "Algo/NoneOf.h"
#include "GameFramework/PlayerState.h"

void AGameStateMenu::BeginPlay()
{
	Super::BeginPlay();

	check(BPScreenManager);
	ScreenManager = NewObject<UScreenManager>(this, BPScreenManager);;
	check(ScreenManager);

	ScreenManager->Start();
}

int AGameStateMenu::ControllerIndex(APlayerControllerMenu const* const PlayerControllerMenu) const
{
	APlayerState* State = PlayerControllerMenu->GetPlayerState<APlayerState>();
	return PlayerArray.IndexOfByPredicate([State](APlayerState const* Other) { return State == Other; });
}

void AGameStateMenu::ProcessInputMain(APlayerControllerMenu const* PlayerControllerMenu) const
{
	ScreenManager->HandleInputMain(ControllerIndex(PlayerControllerMenu));
}

void AGameStateMenu::ProcessInputAlt(APlayerControllerMenu const* PlayerControllerMenu) const
{
	ScreenManager->HandleInputAlt(ControllerIndex(PlayerControllerMenu));
}

void AGameStateMenu::ProcessInputBack(APlayerControllerMenu const* PlayerControllerMenu) const
{
	ScreenManager->HandleInputBack(ControllerIndex(PlayerControllerMenu));
}

void AGameStateMenu::ProcessInputMove(APlayerControllerMenu const* PlayerControllerMenu, FVector2D const& Direction ) const
{
	ScreenManager->HandleInputMove(ControllerIndex(PlayerControllerMenu), Direction);
}

void AGameStateMenu::SetExpectedHumans(uint32 const Humans)
{
	ExpectedHumans = Humans;
}

uint32 AGameStateMenu::GetExpectedHumans() const
{
	return ExpectedHumans;
}

static bool PlayerStateMenuIsTeam(APlayerState const* const PlayerState, ETeam const Team)
{
	APlayerStateMenu const* const PlayerStateMenu = Cast<APlayerStateMenu const>(PlayerState);
	return PlayerStateMenu != nullptr && PlayerStateMenu->Team == Team;
}

bool AGameStateMenu::SetPlayerToTeam(int const PlayerIndex, ETeam const Team)
{
	APlayerStateMenu* const PlayerStateMenu = Cast<APlayerStateMenu>(PlayerArray[PlayerIndex]);
	if (PlayerStateMenu->Team != ETeam::None)
	{
		return false;
	}

	bool const bNone = Algo::NoneOf(PlayerArray, [Team](APlayerState const* const PlayerState){ return PlayerStateMenuIsTeam(PlayerState, Team); });

	if (bNone)
	{
		check(PlayerStateMenu);
		PlayerStateMenu->Team = Team;
	}
	return bNone;
}

void AGameStateMenu::DisassociateTeam(ETeam const Team)
{
	TObjectPtr<APlayerState> const* const Found = PlayerArray.FindByPredicate([Team](APlayerState const* const PlayerState){ return PlayerStateMenuIsTeam(PlayerState, Team); });

	if (Found != nullptr)
	{
		APlayerStateMenu* const PlayerStateMenu = Cast<APlayerStateMenu>(*Found);
		PlayerStateMenu->Team = ETeam::None;
	}
}
