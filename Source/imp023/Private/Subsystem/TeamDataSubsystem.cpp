// Copyright 2024 Impending Technologies


#include "Subsystem/TeamDataSubsystem.h"

#include "Algo/RandomShuffle.h"
#include "Data/TeamData.h"
#include "Engine/AssetManager.h"

void UTeamDataSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	UAssetManager& AssetManager = UAssetManager::Get();

	TArray<FPrimaryAssetId> IdList;
	AssetManager.GetPrimaryAssetIdList("TeamData", IdList);
	TArray<FName> const BundleList;

	AssetManager.LoadPrimaryAssets(IdList, BundleList, FStreamableDelegate::CreateUObject(this, &UTeamDataSubsystem::OnLoadTeamData, IdList));
}

void UTeamDataSubsystem::OnLoadTeamData(TArray<FPrimaryAssetId> IdList)
{
	UAssetManager const& AssetManager = UAssetManager::Get();
	for (FPrimaryAssetId Id : IdList)
	{
		UTeamData const* const TeamDataObject = AssetManager.GetPrimaryAssetObject<UTeamData>(Id);
		TeamData.Add(TeamDataObject);
	}
}

void UTeamDataSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

TArray<UTeamData const*> UTeamDataSubsystem::Choose(size_t const Amount, EChooseMode const Mode) const
{
	check(TeamData.Num() >= Amount);
	TArray<UTeamData const*> Result = TeamData;

	switch (Mode)
	{
		case EChooseMode::Sorted:
			Algo::SortBy(Result, &UTeamData::ID);
			break;
		case EChooseMode::Random:
			Algo::RandomShuffle(Result);
			break;
	}

	if (Result.Num() > Amount)
	{
		Result.RemoveAt(Amount, Result.Num() - Amount);
	}

	return Result;
}
