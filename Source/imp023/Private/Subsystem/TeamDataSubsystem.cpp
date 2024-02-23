// Copyright 2024 Impending Technologies


#include "Subsystem/TeamDataSubsystem.h"

#include "Algo/RandomShuffle.h"

void UTeamDataSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	PlayerData.Emplace(FPlayerData{11, "11", "Cjrostoamotu/Logo", EPlayerPosition::Center, 0.55f, 0.44f, 0.46f, 0.89f, 0.63f});
	PlayerData.Emplace(FPlayerData{12, "12", "Cjrostoamotu/Logo", EPlayerPosition::Bench, 0.73f, 0.39f, 0.46f, 0.86f, 0.71f});
	PlayerData.Emplace(FPlayerData{13, "13", "Cjrostoamotu/Logo", EPlayerPosition::Frantic, 0.68f, 0.52f, 0.82f, 0.59f, 0.58f});
	PlayerData.Emplace(FPlayerData{14, "14", "Cjrostoamotu/Logo", EPlayerPosition::Defend, 0.91f, 0.33f, 0.49f, 0.90f, 0.68f});
	PlayerData.Emplace(FPlayerData{15, "15", "Cjrostoamotu/Logo", EPlayerPosition::Attack2, 0.67f, 0.27f, 0.51f, 0.86f, 0.76f});
	PlayerData.Emplace(FPlayerData{16, "16", "Cjrostoamotu/Logo", EPlayerPosition::Attack1, 0.59f, 0.35f, 0.56f, 0.98f, 0.47f});
	PlayerData.Emplace(FPlayerData{17, "17", "Cjrostoamotu/Logo", EPlayerPosition::Bench, 0.50f, 0.31f, 0.58f, 0.94f, 0.19f});
	PlayerData.Emplace(FPlayerData{18, "18", "Cjrostoamotu/Logo", EPlayerPosition::Bench, 0.08f, 0.37f, 0.51f, 0.90f, 0.06f});

	PlayerData.Emplace(FPlayerData{21, "21", "LakeNatronCrimson/Logo", EPlayerPosition::Bench, 0.55f, 0.79f, 0.41f, 0.31f, 0.24f});
	PlayerData.Emplace(FPlayerData{22, "22", "LakeNatronCrimson/Logo", EPlayerPosition::Bench, 0.78f, 0.08f, 0.56f, 0.27f, 0.76f});
	PlayerData.Emplace(FPlayerData{23, "23", "LakeNatronCrimson/Logo", EPlayerPosition::Defend, 0.73f, 0.44f, 0.53f, 0.22f, 0.59f});
	PlayerData.Emplace(FPlayerData{24, "24", "LakeNatronCrimson/Logo", EPlayerPosition::Frantic, 0.82f, 0.38f, 0.49f, 0.07f, 0.74f});
	PlayerData.Emplace(FPlayerData{25, "25", "LakeNatronCrimson/Logo", EPlayerPosition::Center, 0.71f, 0.38f, 0.53f, 0.41f, 0.77f});
	PlayerData.Emplace(FPlayerData{26, "26", "LakeNatronCrimson/Logo", EPlayerPosition::Bench, 0.60f, 0.37f, 0.05f, 0.63f, 0.65f});
	PlayerData.Emplace(FPlayerData{27, "27", "LakeNatronCrimson/Logo", EPlayerPosition::Attack2, 0.64f, 0.13f, 0.49f, 0.11f, 0.52f});
	PlayerData.Emplace(FPlayerData{28, "28", "LakeNatronCrimson/Logo", EPlayerPosition::Attack1, 0.49f, 0.91f, 0.59f, 0.30f, 0.66f});

	PlayerData.Emplace(FPlayerData{31, "31", "OaxacaAzulOscura/Logo", EPlayerPosition::Center, 0.43f,0.38f,0.77f,0.77f,0.43f});
	PlayerData.Emplace(FPlayerData{32, "32", "OaxacaAzulOscura/Logo", EPlayerPosition::Attack2, 0.48f,0.49f,0.79f,0.52f,0.34f});
	PlayerData.Emplace(FPlayerData{33, "33", "OaxacaAzulOscura/Logo", EPlayerPosition::Bench, 0.86f,0.51f,0.86f,0.07f,0.37f});
	PlayerData.Emplace(FPlayerData{34, "34", "OaxacaAzulOscura/Logo", EPlayerPosition::Attack1, 0.57f,0.38f,0.61f,0.60f,0.39f});
	PlayerData.Emplace(FPlayerData{35, "35", "OaxacaAzulOscura/Logo", EPlayerPosition::Frantic, 0.71f,0.58f,0.60f,0.39f,0.40f});
	PlayerData.Emplace(FPlayerData{36, "36", "OaxacaAzulOscura/Logo", EPlayerPosition::Bench, 0.77f,0.42f,0.77f,0.31f,0.44f});
	PlayerData.Emplace(FPlayerData{37, "37", "OaxacaAzulOscura/Logo", EPlayerPosition::Defend, 0.66f,0.33f,0.80f,0.43f,0.32f});
	PlayerData.Emplace(FPlayerData{38, "38", "OaxacaAzulOscura/Logo", EPlayerPosition::Bench, 0.74f,0.40f,0.58f,0.20f,0.33f});

	PlayerData.Emplace(FPlayerData{41, "41", "PortRoyaleKings/Logo", EPlayerPosition::Bench, 0.46f,0.34f,0.42f,0.74f,0.56f});
	PlayerData.Emplace(FPlayerData{42, "42", "PortRoyaleKings/Logo", EPlayerPosition::Defend, 0.52f,0.43f,0.33f,0.67f,0.75f});
	PlayerData.Emplace(FPlayerData{43, "43", "PortRoyaleKings/Logo", EPlayerPosition::Center, 0.41f,0.33f,0.41f,0.79f,0.84f});
	PlayerData.Emplace(FPlayerData{44, "44", "PortRoyaleKings/Logo", EPlayerPosition::Bench, 0.31f,0.31f,0.44f,0.82f,0.85f});
	PlayerData.Emplace(FPlayerData{45, "45", "PortRoyaleKings/Logo", EPlayerPosition::Bench, 0.58f,0.34f,0.41f,0.83f,0.72f});
	PlayerData.Emplace(FPlayerData{46, "46", "PortRoyaleKings/Logo", EPlayerPosition::Attack2, 0.32f,0.36f,0.91f,0.76f,0.73f});
	PlayerData.Emplace(FPlayerData{47, "47", "PortRoyaleKings/Logo", EPlayerPosition::Attack1, 0.35f,0.31f,0.15f,0.77f,0.73f});
	PlayerData.Emplace(FPlayerData{48, "48", "PortRoyaleKings/Logo", EPlayerPosition::Frantic, 0.27f,0.41f,0.19f,0.77f,0.66f});

	PlayerData.Emplace(FPlayerData{51, "51", "ZelenyyKharkiv/Logo", EPlayerPosition::Frantic, 0.57f,0.50f,0.42f,0.85f,0.84f});
	PlayerData.Emplace(FPlayerData{52, "52", "ZelenyyKharkiv/Logo", EPlayerPosition::Attack1, 0.61f,0.47f,0.50f,0.87f,0.87f});
	PlayerData.Emplace(FPlayerData{53, "53", "ZelenyyKharkiv/Logo", EPlayerPosition::Bench, 0.40f,0.36f,0.53f,0.81f,0.82f});
	PlayerData.Emplace(FPlayerData{54, "54", "ZelenyyKharkiv/Logo", EPlayerPosition::Bench, 0.42f,0.41f,0.74f,0.74f,0.77f});
	PlayerData.Emplace(FPlayerData{55, "55", "ZelenyyKharkiv/Logo", EPlayerPosition::Attack2, 0.26f,0.32f,0.85f,0.68f,0.83f});
	PlayerData.Emplace(FPlayerData{56, "56", "ZelenyyKharkiv/Logo", EPlayerPosition::Bench, 0.23f,0.42f,0.67f,0.88f,0.88f});
	PlayerData.Emplace(FPlayerData{57, "57", "ZelenyyKharkiv/Logo", EPlayerPosition::Defend, 0.44f,0.37f,0.82f,0.93f,0.82f});
	PlayerData.Emplace(FPlayerData{58, "58", "ZelenyyKharkiv/Logo", EPlayerPosition::Center, 0.67f,0.35f,0.49f,0.75f,0.69f});

	PlayerData.Emplace(FPlayerData{61, "61", "ChocenKyanid/Logo", EPlayerPosition::Attack1, 0.57f,0.55f,0.70f,0.37f,0.70f});
	PlayerData.Emplace(FPlayerData{62, "62", "ChocenKyanid/Logo", EPlayerPosition::Defend, 0.41f,0.44f,0.58f,0.28f,0.57f});
	PlayerData.Emplace(FPlayerData{63, "63", "ChocenKyanid/Logo", EPlayerPosition::Bench, 0.45f,0.48f,0.73f,0.26f,0.68f});
	PlayerData.Emplace(FPlayerData{64, "64", "ChocenKyanid/Logo", EPlayerPosition::Bench, 0.56f,0.45f,0.45f,0.44f,0.69f});
	PlayerData.Emplace(FPlayerData{65, "65", "ChocenKyanid/Logo", EPlayerPosition::Frantic, 0.45f,0.46f,0.52f,0.16f,0.64f});
	PlayerData.Emplace(FPlayerData{66, "66", "ChocenKyanid/Logo", EPlayerPosition::Center, 0.38f,0.39f,0.43f,0.22f,0.66f});
	PlayerData.Emplace(FPlayerData{67, "67", "ChocenKyanid/Logo", EPlayerPosition::Bench, 0.46f,0.34f,0.52f,0.11f,0.70f});
	PlayerData.Emplace(FPlayerData{68, "68", "ChocenKyanid/Logo", EPlayerPosition::Attack2, 0.20f,0.35f,0.80f,0.23f,0.54f});

	PlayerData.Emplace(FPlayerData{71, "71", "CroxtethWalledGarden/Logo", EPlayerPosition::Bench, 0.19f,0.64f,0.88f,0.49f,0.91f});
	PlayerData.Emplace(FPlayerData{72, "72", "CroxtethWalledGarden/Logo", EPlayerPosition::Attack2, 0.22f,0.61f,0.89f,0.56f,0.94f});
	PlayerData.Emplace(FPlayerData{73, "73", "CroxtethWalledGarden/Logo", EPlayerPosition::Bench, 0.25f,0.63f,0.84f,0.51f,0.98f});
	PlayerData.Emplace(FPlayerData{74, "74", "CroxtethWalledGarden/Logo", EPlayerPosition::Center, 0.27f,0.66f,0.76f,0.45f,0.86f});
	PlayerData.Emplace(FPlayerData{75, "75", "CroxtethWalledGarden/Logo", EPlayerPosition::Frantic, 0.20f,0.73f,0.87f,0.34f,0.96f});
	PlayerData.Emplace(FPlayerData{76, "76", "CroxtethWalledGarden/Logo", EPlayerPosition::Bench, 0.17f,0.77f,0.81f,0.37f,0.88f});
	PlayerData.Emplace(FPlayerData{77, "77", "CroxtethWalledGarden/Logo", EPlayerPosition::Attack1, 0.16f,0.57f,0.80f,0.45f,0.80f});
	PlayerData.Emplace(FPlayerData{78, "78", "CroxtethWalledGarden/Logo", EPlayerPosition::Defend, 0.14f,0.70f,0.84f,0.33f,0.90f});

	PlayerData.Emplace(FPlayerData{81, "81", "OaklandTrees/Logo", EPlayerPosition::Bench, 0.44f,0.34f,0.45f,0.86f,0.56f});
	PlayerData.Emplace(FPlayerData{82, "82", "OaklandTrees/Logo", EPlayerPosition::Attack1, 0.46f,0.37f,0.50f,0.78f,0.65f});
	PlayerData.Emplace(FPlayerData{83, "83", "OaklandTrees/Logo", EPlayerPosition::Defend, 0.54f,0.36f,0.48f,0.64f,0.64f});
	PlayerData.Emplace(FPlayerData{84, "84", "OaklandTrees/Logo", EPlayerPosition::Attack2, 0.51f,0.31f,0.51f,0.74f,0.72f});
	PlayerData.Emplace(FPlayerData{85, "85", "OaklandTrees/Logo", EPlayerPosition::Center, 0.57f,0.35f,0.52f,0.75f,0.61f});
	PlayerData.Emplace(FPlayerData{86, "86", "OaklandTrees/Logo", EPlayerPosition::Frantic, 0.41f,0.41f,0.56f,0.82f,0.64f});
	PlayerData.Emplace(FPlayerData{87, "87", "OaklandTrees/Logo", EPlayerPosition::Bench, 0.63f,0.23f,0.43f,0.89f,0.51f});
	PlayerData.Emplace(FPlayerData{88, "88", "OaklandTrees/Logo", EPlayerPosition::Bench, 0.52f,0.39f,0.42f,0.84f,0.60f});

	TeamData.Emplace(FTeamData{1, "Cjrostoamotu", "CJR", "Cjrostoamotu", FLinearColor::Gray, {P(11), P(12), P(13), P(14), P(15), P(16), P(17), P(18)}});
	TeamData.Emplace(FTeamData{2, "Lake Natron Crimson", "LNC", "LakeNatronCrimson", FLinearColor::Red, {P(21), P(22), P(23), P(24), P(25), P(26), P(27), P(28)}});
	TeamData.Emplace(FTeamData{3, "Oaxaca Azul Oscura", "OAO", "OaxacaAzulOscura", FLinearColor::Blue, {P(31), P(32), P(33), P(34), P(35), P(36), P(37), P(38)}});
	TeamData.Emplace(FTeamData{4, "Port Royale Kings", "PRK", "PortRoyaleKings", FLinearColor(0.75f, 0.0f, 0.75f, 1.0f), {P(41), P(42), P(43), P(44), P(45), P(46), P(47), P(48)}});
	TeamData.Emplace(FTeamData{5, "Zelenyy Kharkiv", "KHA", "ZelenyyKharkiv", FLinearColor::Green, {P(51), P(52), P(53), P(54), P(55), P(56), P(57), P(58)}});
	TeamData.Emplace(FTeamData{6, "Chocen Kyanid", "CHK", "ChocenKyanid", FLinearColor(0.0f, 0.75f, 0.75f, 1.0f), {P(61), P(62), P(63), P(64), P(65), P(66), P(67), P(68)}});
	TeamData.Emplace(FTeamData{7, "Croxteth Walled Garden", "CWG", "CroxtethWalledGarden", FLinearColor::Yellow, {P(71), P(72), P(73), P(74), P(75), P(76), P(77), P(78)}});
	TeamData.Emplace(FTeamData{8, "Oakland Trees", "OAK", "OaklandTrees", FLinearColor(0.80f, 0.46f, 0.13f, 1.0f), {P(81), P(82), P(83), P(84), P(85), P(86), P(87), P(88)}});
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

FPlayerData* UTeamDataSubsystem::P(uint32_t const ID)
{
	return PlayerData.FindByKey(ID);
}
