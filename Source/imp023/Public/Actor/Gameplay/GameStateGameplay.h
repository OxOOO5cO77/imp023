// Copyright 2024 Impending Technologies

#pragma once

#include "CoreMinimal.h"
#include "Component/CompTeam.h"
#include "Component/CompZone.h"
#include "GameFramework/GameStateBase.h"
#include "UI/Manager/ScreenManager.h"
#include "GameStateGameplay.generated.h"

class APlayerControllerGameplay;

UENUM(BlueprintType)
enum class EGameplayGameState : uint8
{
	PreMatch,	// load?
	PrePeriod,	// show team orientation
	PrePlay,	// countdown
	Play,		// gameplay
	PostPlay,	// goal
	PostPeriod,	// show period summary
	PostMatch,	// show game summary

	Max
};

DECLARE_MULTICAST_DELEGATE_OneParam(FStateChangeEvent, EGameplayGameState);
DECLARE_MULTICAST_DELEGATE_OneParam(FUpdateScoresEvent, TArray<int> const&);
DECLARE_MULTICAST_DELEGATE_TwoParams(FChangeZoneEvent, EZone, EZone);

/**
 *
 */
UCLASS()
class IMP023_API AGameStateGameplay : public AGameStateBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	FStateChangeEvent StateChangeEvent;
	FUpdateScoresEvent UpdateScoresEvent;
	FChangeZoneEvent ChangeZoneEvent;

public:
	UFUNCTION(BlueprintPure)
	bool IsState(EGameplayGameState State) const;

	UFUNCTION(BlueprintPure)
	EZone GetCurrentZone() const;

	UFUNCTION(BlueprintPure)
	FLinearColor GetTeamColorForPeriod(ETeam const Team) const;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int Period;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<int32> Score;

public:
	void SetCurrentTeamTouched(ETeam const Team);
	void ChangeZone(EZone const Zone);
	void ScoreGoal(ETeam const Team);
	void ResetGameplay();
	void BroadcastScores() const;
	void SetState(EGameplayGameState const State);
	APlayerController* GetPlayerControllerFromTeam(ETeam const Team);
	void ProcessInputMain(APlayerControllerGameplay* PlayerControllerGameplay) const;
	float GetTimerDelayRemaining() const;
	float GetPeriodTimeRemainingPercent() const;
	FLinearColor GetTeamColor(ETeam const Team) const;

private:
	FTimerHandle TimerPeriod;
	FTimerHandle TimerDelay;

private:
	EGameplayGameState CurrentGameState;
	EZone CurrentZone;
	EZone PreviousZone;
	ETeam CurrentTeamTouched;
	ETeam PreviousTeamTouched;

private:
	void SetState_PreMatch();
	void SetState_PrePeriod();
	void SetState_PrePlay();
	void SetState_Play();
	void SetState_PostPlay();
	void SetState_PostPeriod();
	void SetState_PostMatch();

	void DelayedStateChange(EGameplayGameState NewState, float Delay);

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ScreenManager", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UScreenManager> BPScreenManager;

	UPROPERTY()
	UScreenManager* ScreenManager;
};
