// Copyright 2024 Impending Technologies

#include "Actor/Menu/GameStateMenu.h"

#include "Actor/Menu/PlayerStateMenu.h"
#include "Algo/NoneOf.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerState.h"
#include "UI/Menu/Screen.h"

AGameStateMenu::AGameStateMenu()
{
	CurScreen = nullptr;
}

void AGameStateMenu::BeginPlay()
{
	Super::BeginPlay();

	NavigateTo(Default);
}

void AGameStateMenu::NavigateTo(FString const& Screen)
{
	check(ScreenMap.Contains(Screen));

	if (CurScreen != nullptr)
	{
		CurScreen->RemoveFromParent();
		CurScreen = nullptr;
	}

	TSubclassOf<UUserWidget> const Destination = ScreenMap[Screen];

	if (Destination != nullptr)
	{
		CurScreen = CreateWidget<UScreen>(GetWorld(), Destination);
		if (CurScreen != nullptr)
		{
			CurScreen->AddToViewport();
		}
	}
}

int AGameStateMenu::ControllerIndex(APlayerControllerMenu const* const PlayerControllerMenu) const
{
	APlayerState* State = PlayerControllerMenu->GetPlayerState<APlayerState>();
	return PlayerArray.IndexOfByPredicate([State](APlayerState const* Other) { return State == Other; });
}

void AGameStateMenu::ProcessInputMain(APlayerControllerMenu const* PlayerControllerMenu) const
{
	CurScreen->HandleInputMain(ControllerIndex(PlayerControllerMenu));
}

void AGameStateMenu::ProcessInputAlt(APlayerControllerMenu const* PlayerControllerMenu) const
{
	CurScreen->HandleInputAlt(ControllerIndex(PlayerControllerMenu));
}

void AGameStateMenu::ProcessInputBack(APlayerControllerMenu const* PlayerControllerMenu) const
{
	CurScreen->HandleInputBack(ControllerIndex(PlayerControllerMenu));
}

static bool StateIsTeam(APlayerState* const PlayerState, ETeam const Team)
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

	using namespace std::placeholders;
	bool const bNone = Algo::NoneOf(PlayerArray, std::bind(&StateIsTeam, _1, Team));

	if (bNone)
	{
		check(PlayerStateMenu);
		PlayerStateMenu->Team = Team;
	}
	return bNone;
}

void AGameStateMenu::DisassociateTeam(ETeam const Team)
{
	using namespace std::placeholders;
	TObjectPtr<APlayerState> const* const Found = PlayerArray.FindByPredicate(std::bind(&StateIsTeam, _1, Team));

	if (Found != nullptr)
	{
		APlayerStateMenu* const PlayerStateMenu = Cast<APlayerStateMenu>(*Found);
		PlayerStateMenu->Team = ETeam::None;
	}
}
