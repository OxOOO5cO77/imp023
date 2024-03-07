// Copyright 2024 Impending Technologies

#pragma once

#include "CoreMinimal.h"
#include "Subsystem/LeagueSubsystem.h"
#include "UI/Manager/Screen.h"
#include "ScreenTeamSelect.generated.h"

class UPartTeam;
/**
 *
 */
UCLASS()
class IMP023_API UScreenTeamSelect : public UScreen
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;
	virtual void OnInputMain(int const PlayerIndex) override;
	virtual void OnInputBack(int const PlayerIndex) override;
	virtual void OnInputUp(int const PlayerIndex) override;
	virtual void OnInputDown(int const PlayerIndex) override;

private:
	UPartTeam const* Part(uint32 const Index) const;
	void NextTrackedIndex();
	void PrevTrackedIndex();

private:
	UPROPERTY()
	UPartTeam* Team1;
	UPROPERTY()
	UPartTeam* Team2;
	UPROPERTY()
	UPartTeam* Team3;
	UPROPERTY()
	UPartTeam* Team4;
	UPROPERTY()
	UPartTeam* Team5;
	UPROPERTY()
	UPartTeam* Team6;
	UPROPERTY()
	UPartTeam* Team7;
	UPROPERTY()
	UPartTeam* Team8;

	uint32 TrackedSlotIndex;
	TArray<FLeagueTeam> Teams;
};
