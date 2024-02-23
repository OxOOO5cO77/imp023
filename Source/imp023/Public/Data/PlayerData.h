#pragma once

enum class EPlayerPosition
{
	Bench,
	Center,
	Defend,
	Attack1,
	Attack2,
	Frantic,
};

struct FPlayerData
{
	uint32_t ID;
	FString Name;
	FString Image;
	EPlayerPosition Position;
	float Rate;
	float Power;
	float Slide;
	float Boing;
	float Mass;

	bool operator==(uint32_t const RHS) const;

	float RateAsMaxVelocity() const;
	float PowerAsImpulse() const;
	float PowerAsBoost() const;
	float SlideAsFriction() const;
	float BoingAsRestitution() const;

	static int Attr(float const InValue);
};
