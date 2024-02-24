// Copyright 2024 Impending Technologies


#include "Data/TeamData.h"

#include "Algo/Count.h"
#include "Misc/DataValidation.h"

using namespace std::placeholders;

static bool PredPlayerPosition(UPlayerData const* const Player, EPlayerPosition const Check)
{
	return Player && Player->Position == Check;
}

UPlayerData const* UTeamData::PlayerByPosition(EPlayerPosition const Position) const
{
	UPlayerData const* const* Result = Players.FindByPredicate(std::bind(&PredPlayerPosition, _1, Position));;
	return Result ? *Result : nullptr;
}

#if WITH_EDITOR
void UTeamData::Validate_PlayerCount(FDataValidationContext& Context, EDataValidationResult& Result) const
{
	if (Players.Num() != 8)
	{
		Context.AddError(FText::FromString("Players must be 8"));
		Result = EDataValidationResult::Invalid;
	}
}

void UTeamData::Validate_PlayerValidCount(FDataValidationContext& Context, EDataValidationResult& Result) const
{
	int const ValidCount = Algo::CountIf(Players, [](TAssetPtr<UPlayerData> const& Player) { return !Player.IsValid(); });
	if (ValidCount > 0)
	{
		Context.AddError(FText::FormatOrdered(INVTEXT("Players contains {0} empty members"), ValidCount));
		Result = EDataValidationResult::Invalid;
	}
}

void UTeamData::Validate_PlayerPositions(FDataValidationContext& Context, EDataValidationResult& Result) const
{
	EPlayerPosition ToCheck[5] = {EPlayerPosition::Center, EPlayerPosition::Defend, EPlayerPosition::Attack1, EPlayerPosition::Attack2, EPlayerPosition::Frantic};
	for (EPlayerPosition Check : ToCheck)
	{
		int const PositionCount = Algo::CountIf(Players, std::bind(&PredPlayerPosition, _1, Check));
		if (PositionCount == 0)
		{
			Context.AddError(FText::FormatOrdered(INVTEXT("Players missing Position: {0}"), static_cast<int>(Check)));
			Result = EDataValidationResult::Invalid;
		}
		else if (PositionCount > 1)
		{
			Context.AddError(FText::FormatOrdered(INVTEXT("Players Duplicate Position: {0} ({1} instances)"), static_cast<int>(Check), PositionCount));
			Result = EDataValidationResult::Invalid;
		}
	}
}

EDataValidationResult UTeamData::IsDataValid(FDataValidationContext& Context) const
{
	EDataValidationResult Result = EDataValidationResult::Valid;
	Validate_PlayerCount(Context, Result);
	Validate_PlayerValidCount(Context, Result);
	Validate_PlayerPositions(Context, Result);
	if (Result == EDataValidationResult::Invalid)
	{
		return Result;
	}

	return Super::IsDataValid(Context);
}
#endif
