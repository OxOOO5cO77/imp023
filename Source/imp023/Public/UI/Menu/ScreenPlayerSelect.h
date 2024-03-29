// Copyright 2024 Impending Technologies

#pragma once

#include "CoreMinimal.h"
#include "Subsystem/LeagueSubsystem.h"
#include "UI/Manager/Screen.h"
#include "ScreenPlayerSelect.generated.h"

class UPartTeam;
/**
 *
 */
UCLASS()
class IMP023_API UScreenPlayerSelect : public UScreen
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

protected:
	virtual void OnInputMain(int const PlayerIndex) override;
	virtual void OnInputBack(int const PlayerIndex) override;

private:
	UPartTeam* Part(uint32 const PartIndex) const;
	void NextTrackedIndex();
	void PrevTrackedIndex();

private:
	UPROPERTY()
	UPartTeam* TeamHome;
	UPROPERTY()
	UPartTeam* TeamAway1;
	UPROPERTY()
	UPartTeam* TeamAway2;

	TArray<FLeagueTeamForMatch> MatchTeams;
	uint32 TrackedSlotIndex;
};
