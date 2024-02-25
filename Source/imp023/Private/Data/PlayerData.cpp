// Copyright 2024 Impending Technologies


#include "Data/PlayerData.h"

void UPlayerData::GetAssetRegistryTags(TArray<FAssetRegistryTag>& OutTags) const
{
	Super::GetAssetRegistryTags(OutTags);

	OutTags.Add(FAssetRegistryTag("Position", PositionAsString(), FAssetRegistryTag::TT_Alphabetical));
	OutTags.Add(FAssetRegistryTag("Rate", FString::FromInt(Attr(Rate)), FAssetRegistryTag::TT_Numerical));
	OutTags.Add(FAssetRegistryTag("Power", FString::FromInt(Attr(Power)), FAssetRegistryTag::TT_Numerical));
	OutTags.Add(FAssetRegistryTag("Slide", FString::FromInt(Attr(Slide)), FAssetRegistryTag::TT_Numerical));
	OutTags.Add(FAssetRegistryTag("Boing", FString::FromInt(Attr(Boing)), FAssetRegistryTag::TT_Numerical));
	OutTags.Add(FAssetRegistryTag("Mass", FString::FromInt(Attr(Mass)), FAssetRegistryTag::TT_Numerical));
}

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

FString UPlayerData::PositionAsString() const
{
	switch (Position)
	{
		case EPlayerPosition::Bench:
			return TEXT("Bench");
		case EPlayerPosition::Center:
			return TEXT("Center");
		case EPlayerPosition::Defend:
			return TEXT("Defend");
		case EPlayerPosition::Attack1:
			return TEXT("Attack1");
		case EPlayerPosition::Attack2:
			return TEXT("Attack2");
		case EPlayerPosition::Frantic:
			return TEXT("Frantic");
		default:
			checkNoEntry();
			break;
	}
	return TEXT("Unknown");
}

int UPlayerData::Attr(float const InValue)
{
	return FGenericPlatformMath::RoundToInt(InValue * 100.0f);
}
