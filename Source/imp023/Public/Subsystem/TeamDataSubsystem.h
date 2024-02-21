// Copyright 2024 Impending Technologies

#pragma once

#include "CoreMinimal.h"
#include "Data/TeamData.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "TeamDataSubsystem.generated.h"

/**
 *
 */
UCLASS()
class IMP023_API UTeamDataSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

public:
	TArray<FTeamData> ChooseThree() const;

private:
	TArray<FTeamData> TeamData;
};
