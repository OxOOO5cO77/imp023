// Copyright 2024 Impending Technologies

#include "Component/CompTeam.h"

UCompTeam::UCompTeam()
{
	PrimaryComponentTick.bCanEverTick = false;

	Team = ETeam::None;
}

void UCompTeam::Set(ETeam const Value)
{
	Team = Value;
	UpdateTeamEvent.Broadcast(Value);
}
