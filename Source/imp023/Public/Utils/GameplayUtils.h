// Copyright 2024 Impending Technologies

#pragma once

#include "Enum/ELocator.h"
#include "Enum/ETeam.h"
#include "Enum/EZone.h"
#include "Data/PlayerData.h"

class FGameplayUtils
{
public:
	static ETeam MapZoneLocatorToTeamPeriod(EZone const ZoneFrom, EZone const ZoneTo, ELocator const Locator, int const Period);
	static ETeam MapPeriodTeamToTeam(int const Period, ETeam const Source);
	static EPlayerPosition MapZoneTeamToPlayerPosition(EZone const Zone, ETeam const Team);
};
