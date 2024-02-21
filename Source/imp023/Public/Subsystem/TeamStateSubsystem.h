// Copyright 2024 Impending Technologies

#pragma once

#include "CoreMinimal.h"
#include "Component/CompTeam.h"
#include "Data/TeamData.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "TeamStateSubsystem.generated.h"

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

private:
	TMap<ETeam,FTeamData> TeamMap;
};
