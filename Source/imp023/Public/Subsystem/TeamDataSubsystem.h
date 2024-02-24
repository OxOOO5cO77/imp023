// Copyright 2024 Impending Technologies

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "TeamDataSubsystem.generated.h"

class UTeamData;
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
	TArray<UTeamData*> ChooseThree() const;

private:
	void OnLoadTeamData(FPrimaryAssetId Id);
private:
	TArray<UTeamData*> TeamData;
};
