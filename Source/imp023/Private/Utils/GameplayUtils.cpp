// Copyright 2024 Impending Technologies

#include "Utils/GameplayUtils.h"

static ETeam const* MapZonesToTeam(EZone const ZoneFrom, EZone const ZoneTo)
{
	//								ignore		north		east		   south		west
	static ETeam A1A2NoHo[5] = {ETeam::None, ETeam::Away1, ETeam::Away2, ETeam::None, ETeam::Home};
	static ETeam A1A2HoNo[5] = {ETeam::None, ETeam::Away1, ETeam::Away2, ETeam::Home, ETeam::None};
	static ETeam NoA2A1Ho[5] = {ETeam::None, ETeam::None, ETeam::Away2, ETeam::Away1, ETeam::Home};
	static ETeam A1NoA2Ho[5] = {ETeam::None, ETeam::Away1, ETeam::None, ETeam::Away2, ETeam::Home};

	switch (ZoneTo)
	{
		case EZone::North:
			return A1A2NoHo;
		case EZone::East:
			return A1A2HoNo;
		case EZone::South:
			return NoA2A1Ho;
		case EZone::West:
			return A1NoA2Ho;
		case EZone::Middle:
			switch (ZoneFrom)
			{
				case EZone::Middle:
				case EZone::South:
					return A1A2NoHo;
				case EZone::North:
					return NoA2A1Ho;
				case EZone::East:
					return A1NoA2Ho;
				case EZone::West:
					return A1A2HoNo;
			}
			break;
	}
	return nullptr;
}

ETeam FGameplayUtils::MapZoneLocatorToTeamPeriod(EZone const ZoneFrom, EZone const ZoneTo, ELocator const Locator, int const Period)
{
	int const Index = static_cast<int>(Locator);
	ETeam const* Teams = MapZonesToTeam(ZoneFrom, ZoneTo);
	return MapPeriodTeamToTeam(Period, Teams[Index]);
}

ETeam FGameplayUtils::MapPeriodTeamToTeam(int const Period, ETeam const Source)
{
	switch (Period)
	{
		case 2:
			switch (Source)
			{
				case ETeam::Home:
					return ETeam::Away2;
				case ETeam::Away1:
					return ETeam::Home;
				case ETeam::Away2:
					return ETeam::Away1;
				default:
					break;
			}
			break;
		case 3:
			switch (Source)
			{
				case ETeam::Home:
					return ETeam::Away1;
				case ETeam::Away1:
					return ETeam::Away2;
				case ETeam::Away2:
					return ETeam::Home;
				default:
					break;
			}
			break;
		default:
			break;
	}
	return Source;
}
