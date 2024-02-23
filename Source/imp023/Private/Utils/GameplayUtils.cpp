// Copyright 2024 Impending Technologies

#include "Utils/GameplayUtils.h"

static ETeam const* MapZonesToTeam(EZone const ZoneFrom, EZone const ZoneTo)
{
	//								ignore		north		east		   south		west
	static ETeam HoA2NoA1[5] = {ETeam::None, ETeam::Home, ETeam::Away2, ETeam::None, ETeam::Away1};
	static ETeam HoA2A1No[5] = {ETeam::None, ETeam::Home, ETeam::Away2, ETeam::Away1, ETeam::None};
	static ETeam NoA2HoA1[5] = {ETeam::None, ETeam::None, ETeam::Away2, ETeam::Home, ETeam::Away1};
	static ETeam HoNoA2A1[5] = {ETeam::None, ETeam::Home, ETeam::None, ETeam::Away2, ETeam::Away1};

	switch (ZoneTo)
	{
		case EZone::North:
			return HoA2NoA1;
		case EZone::East:
			return HoA2A1No;
		case EZone::South:
			return NoA2HoA1;
		case EZone::West:
			return HoNoA2A1;
		case EZone::Middle:
			switch (ZoneFrom)
			{
				case EZone::Middle:
				case EZone::South:
					return HoA2NoA1;
				case EZone::North:
					return NoA2HoA1;
				case EZone::East:
					return HoNoA2A1;
				case EZone::West:
					return HoA2A1No;
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
					return ETeam::Away1;
				case ETeam::Away1:
					return ETeam::Away2;
				case ETeam::Away2:
					return ETeam::Home;
				default:
					break;
			}
			break;
		case 3:
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
		default:
			break;
	}
	return Source;
}

EPlayerPosition FGameplayUtils::MapZoneTeamToPlayerPosition(EZone const Zone, ETeam const Team)
{
	switch (Zone)
	{
		case EZone::Middle:
			return EPlayerPosition::Center;
		case EZone::North:
			switch (Team)
			{
				case ETeam::Home:
					return EPlayerPosition::Defend;
				case ETeam::Away1:
					return EPlayerPosition::Attack1;
				case ETeam::Away2:
					return EPlayerPosition::Attack2;
				default:
					break;
			}
			break;
		case EZone::East:
			switch (Team)
			{
				case ETeam::Home:
					return EPlayerPosition::Attack1;
				case ETeam::Away1:
					return EPlayerPosition::Attack2;
				case ETeam::Away2:
					return EPlayerPosition::Defend;
				default:
					break;
			}
			break;
		case EZone::South:
			return EPlayerPosition::Frantic;
		case EZone::West:
			switch (Team)
			{
				case ETeam::Home:
					return EPlayerPosition::Attack2;
				case ETeam::Away1:
					return EPlayerPosition::Defend;
				case ETeam::Away2:
					return EPlayerPosition::Attack1;
				default:
					break;
			}
			break;
	}
	return EPlayerPosition::Bench;
}
