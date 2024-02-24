// Copyright 2024 Impending Technologies


#include "Data/PlayerData.h"

bool UPlayerData::operator==(uint32_t const RHS) const
{
	return ID == RHS;
}

float UPlayerData::RateAsMaxVelocity() const
{
	return 1000.0f * Rate;
}

float UPlayerData::PowerAsImpulse() const
{
	return std::lerp(15.0f, 30.0f, Power);
}

float UPlayerData::PowerAsBoost() const
{
	return std::lerp(1000.0f, 2000.0f, Power);
}

float UPlayerData::SlideAsFriction() const
{
	return 1.0f - std::lerp(0.5f, 1.0f, Slide);
}

float UPlayerData::BoingAsRestitution() const
{
	return std::lerp(0.5f, 1.0f, Boing);
}

int UPlayerData::Attr(float const InValue)
{
	return FGenericPlatformMath::RoundToInt(InValue * 100.0f);
}
