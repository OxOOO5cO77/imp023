#include "Data/PlayerData.h"

bool FPlayerData::operator==(uint32_t const RHS) const
{
	return ID == RHS;
}

float FPlayerData::RateAsMaxVelocity() const
{
	return 1000.0f * Rate;
}

float FPlayerData::PowerAsImpulse() const
{
	return std::lerp(15.0f, 30.0f, Power);
}

float FPlayerData::PowerAsBoost() const
{
	return std::lerp(1000.0f, 2000.0f, Power);
}

float FPlayerData::SlideAsFriction() const
{
	return 1.0f - std::lerp(0.5f, 1.0f, Slide);
}

float FPlayerData::BoingAsRestitution() const
{
	return std::lerp(0.5f, 1.0f, Boing);
}

int FPlayerData::Attr(float const InValue)
{
	return FGenericPlatformMath::RoundToInt(InValue * 100.0f);
}
