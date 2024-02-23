#pragma once
#include "PlayerData.h"

struct FTeamData
{
	uint32_t ID;
	FString Name;
	FString Abbrev;
	FString AssetPath;
	FLinearColor Color;
	FPlayerData const* Players[8];

	FPlayerData const* PlayerByPosition(EPlayerPosition const Position) const;
};
