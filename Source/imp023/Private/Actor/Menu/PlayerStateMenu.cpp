// Copyright 2024 Impending Technologies


#include "Actor/Menu/PlayerStateMenu.h"

#include "Actor/Player/PlayerStateGameplay.h"

APlayerStateMenu::APlayerStateMenu()
	: Team(ETeam::None)
{
}

void APlayerStateMenu::CopyProperties(APlayerState* PlayerState)
{
	Super::CopyProperties(PlayerState);

	APlayerStateGameplay* PlayerStateGameplay = Cast<APlayerStateGameplay>(PlayerState);
	check(PlayerStateGameplay);

	PlayerStateGameplay->Team = Team;
}

