// Copyright 2024 Impending Technologies

#pragma once

#include "CoreMinimal.h"
#include "Component/CompTeam.h"
#include "Component/CompZone.h"
#include "GameFramework/GameStateBase.h"
#include "GameStateGameplay.generated.h"

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
	DECLARE_EVENT_OneParam(AGameStateGameplay, FStateChangeEvent, EGameplayGameState)
	FStateChangeEvent& OnStateChange() { return StateChangeEvent; }

	DECLARE_EVENT_OneParam(AGameStateGameplay, FUpdateScoresEvent, TArray<int> const&)
	FUpdateScoresEvent& OnUpdateScores() { return UpdateScoresEvent; }

public:
	UFUNCTION(BlueprintPure)
	bool IsState(EGameplayGameState State) const;

	UFUNCTION(BlueprintPure)
	EZone GetCurrentZone() const;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int Period;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<int32> Score;

public:
	void SetCurrentTeamTouched(ETeam const Team);
	void ChangeZone(EZone const Zone);
	void ScoreGoal(ETeam const Team);
	void ResetTracking();
	void SetState(EGameplayGameState const State);
	APlayerController* GetPlayerControllerFromTeam(ETeam const Team);

private:
	FTimerHandle TimerPeriod;
	FStateChangeEvent StateChangeEvent;
	FUpdateScoresEvent UpdateScoresEvent;

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

	void OnPeriodEnd();

	void DelayedStateChange(EGameplayGameState NewState, float Delay);
};
