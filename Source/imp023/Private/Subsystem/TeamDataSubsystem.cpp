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

	for (FPrimaryAssetId& Id : IdList)
	{
		AssetManager.LoadPrimaryAsset(Id, BundleList, FStreamableDelegate::CreateUObject(this, &UTeamDataSubsystem::OnLoadTeamData, Id));;
	}
}

void UTeamDataSubsystem::OnLoadTeamData(FPrimaryAssetId Id)
{
	UAssetManager const& AssetManager = UAssetManager::Get();
	UTeamData* TeamDataObject = AssetManager.GetPrimaryAssetObject<UTeamData>(Id);
	TeamData.Add(TeamDataObject);
}

void UTeamDataSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

TArray<UTeamData*> UTeamDataSubsystem::ChooseThree() const
{
	check(TeamData.Num() >= 3);

	TArray<UTeamData*> Result = TeamData;

	Algo::RandomShuffle(Result);

	Result.RemoveAt(3, Result.Num() - 3);

	return Result;
}
