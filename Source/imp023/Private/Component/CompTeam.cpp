// Copyright 2024 Impending Technologies

#include "Component/CompTeam.h"

UCompTeam::UCompTeam()
{
	PrimaryComponentTick.bCanEverTick = false;

	Team = ETeam::None;
}
