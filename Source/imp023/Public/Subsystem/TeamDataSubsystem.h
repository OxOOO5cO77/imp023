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
	enum class EChooseMode
	{
		Sorted,
		Random,
	};
	TArray<UTeamData const*> Choose(size_t const Amount, EChooseMode const Mode) const;

private:
	void OnLoadTeamData(TArray<FPrimaryAssetId> IdList);
private:
	TArray<UTeamData const*> TeamData;
};
