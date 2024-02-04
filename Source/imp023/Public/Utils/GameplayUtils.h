// Copyright 2024 Impending Technologies

#pragma once

#include "Component/CompLocator.h"
#include "Component/CompTeam.h"
#include "Component/CompZone.h"

class FGameplayUtils
{
public:
	static ETeam MapZoneLocatorToTeam(EZone const ZoneFrom, EZone const ZoneTo, ELocator const Locator);
	static ETeam MapPeriodTeamToTeam(int const Period, ETeam const Source);
};
