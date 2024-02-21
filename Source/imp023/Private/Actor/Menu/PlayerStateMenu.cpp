// Copyright 2024 Impending Technologies


#include "Actor/Menu/PlayerStateMenu.h"

#include "Actor/Gameplay/PlayerStateGameplay.h"

APlayerStateMenu::APlayerStateMenu()
	: Team(ETeam::None)
{
}

void APlayerStateMenu::CopyProperties(APlayerState* PlayerState)
{
	Super::CopyProperties(PlayerState);

	APlayerStateGameplay* PlayerStateGameplay = CastChecked<APlayerStateGameplay>(PlayerState);

	PlayerStateGameplay->Team = Team;
}
