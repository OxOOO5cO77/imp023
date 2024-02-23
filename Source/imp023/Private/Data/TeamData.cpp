#include "Data/TeamData.h"

FPlayerData const* FTeamData::PlayerByPosition(EPlayerPosition const Position) const
{
	return *Algo::FindByPredicate(Players, [Position](FPlayerData const* const Player) { return Player->Position == Position; });
}
