// Copyright 2024 Impending Technologies


#include "Subsystem/TeamDataSubsystem.h"

#include "Algo/RandomShuffle.h"

void UTeamDataSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	TeamData.Emplace(FTeamData{1, "Cjrostoamotu", "CJR", "Cjrostoamotu", FLinearColor::Gray});
	TeamData.Emplace(FTeamData{2, "Lake Natron Crimson", "LNC", "LakeNatronCrimson", FLinearColor::Red});
	TeamData.Emplace(FTeamData{3, "Oaxaca Azul Oscura", "OAO", "OaxacaAzulOscura", FLinearColor::Blue});
	TeamData.Emplace(FTeamData{4, "Port Royale Kings", "PRK", "PortRoyaleKings", FLinearColor(0.75f, 0.0f, 0.75f, 1.0f)});
	TeamData.Emplace(FTeamData{5, "Zelenyy Kharkiv", "KHA", "ZelenyyKharkiv", FLinearColor::Green});
}

void UTeamDataSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

TArray<FTeamData> UTeamDataSubsystem::ChooseThree() const
{
	check(TeamData.Num() >= 3);

	TArray<FTeamData> Result = TeamData;

	Algo::RandomShuffle(Result);

	Result.RemoveAt(3, Result.Num() - 3);

	return Result;
}