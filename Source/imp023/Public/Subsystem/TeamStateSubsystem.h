// Copyright 2024 Impending Technologies

#pragma once

#include "CoreMinimal.h"
#include "Component/CompTeam.h"
#include "Data/PlayerData.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "TeamStateSubsystem.generated.h"

class UTeamData;
/**
 *
 */
UCLASS()
class IMP023_API UTeamStateSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	void InitializeTeams();

	UTexture2D* GetLogo(UObject* const Outer, ETeam const Team) const;
	FLinearColor GetColor(ETeam Team) const;
	FString GetAbbrev(ETeam Team) const;
	UPlayerData const* GetTeamPlayer(ETeam const Team, EPlayerPosition const PlayerPosition) const;

private:
	TMap<ETeam,UTeamData*> TeamMap;
};
