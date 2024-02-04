// Copyright 2024 Impending Technologies

#include "Actor/Game/GameStateGameplay.h"

#include "Actor/Game/GameModeGameplay.h"
#include "Kismet/GameplayStatics.h"
#include "Utils/GameplayUtils.h"

void AGameStateGameplay::BeginPlay()
{
	Super::BeginPlay();

	SetState(EGameplayGameState::PreMatch);
}

void AGameStateGameplay::ChangeZone(EZone const Zone)
{
	AGameModeGameplay const* const GameMode = Cast<AGameModeGameplay>(UGameplayStatics::GetGameMode(this));

	GameMode->ResetActorsForZone(Zone, CurrentZone);	// reset players in the leaving zone (CurrentZone) as if the ball was coming from the new zone (Zone)
	GameMode->HandlePossession(Zone);

	PreviousZone = CurrentZone;
	CurrentZone = Zone;
}

void AGameStateGameplay::SetCurrentTeamTouched(ETeam const Team)
{
	if (Team == CurrentTeamTouched)
	{
		return;
	}

	PreviousTeamTouched = CurrentTeamTouched;
	CurrentTeamTouched = Team;
}

void AGameStateGameplay::ScoreGoal(ETeam const Team)
{
	ETeam const GoalTeam = FGameplayUtils::MapPeriodTeamToTeam(Period, Team);
	ETeam const ScoringTeam = CurrentTeamTouched != GoalTeam ? CurrentTeamTouched : PreviousTeamTouched;

	if (ScoringTeam != ETeam::None)
	{
		Score[static_cast<int>(ScoringTeam)]++;
	}
	else
	{
		Score[static_cast<int>(ETeam::Home)] += CurrentTeamTouched == ETeam::Home ? 0 : 1;
		Score[static_cast<int>(ETeam::Away1)] += CurrentTeamTouched == ETeam::Away1 ? 0 : 1;
		Score[static_cast<int>(ETeam::Away2)] += CurrentTeamTouched == ETeam::Away2 ? 0 : 1;
	}

	UpdateScoresEvent.Broadcast(Score);

	AGameModeGameplay const* const GameMode = Cast<AGameModeGameplay>(UGameplayStatics::GetGameMode(this));

	GameMode->ResetActorsForZone(EZone::Middle, EZone::Middle);	// reset players in the leaving zone (CurrentZone) as if the ball was coming from the new zone (Zone)

	SetState(EGameplayGameState::PostPlay);
}

void AGameStateGameplay::ResetTracking()
{
	PreviousZone = EZone::Middle;
	CurrentZone = EZone::Middle;

	PreviousTeamTouched = ETeam::None;
	CurrentTeamTouched = ETeam::None;
}

void AGameStateGameplay::SetState_PreMatch()
{
	Period = 0;
	Score.Init(0, 4);
	SetState(EGameplayGameState::PrePeriod);
}

void AGameStateGameplay::SetState_PrePeriod()
{
	Period += 1;

	FTimerManager& TM = GetWorld()->GetTimerManager();
	TM.SetTimer(TimerPeriod, this, &AGameStateGameplay::OnPeriodEnd, 90.0f);
	TM.PauseTimer(TimerPeriod);

	SetState(EGameplayGameState::PrePlay);
}

void AGameStateGameplay::SetState_PrePlay()
{
	GetWorld()->GetTimerManager().PauseTimer(TimerPeriod);
	ResetTracking();

	DelayedStateChange(EGameplayGameState::Play, 3.0f);
}

void AGameStateGameplay::SetState_Play()
{
	GetWorld()->GetTimerManager().UnPauseTimer(TimerPeriod);
}

void AGameStateGameplay::SetState_PostPlay()
{
	GetWorld()->GetTimerManager().PauseTimer(TimerPeriod);

	DelayedStateChange(EGameplayGameState::PrePlay, 3.0f);
}

void AGameStateGameplay::SetState_PostPeriod()
{
	DelayedStateChange(EGameplayGameState::PrePeriod, 3.0f);
}

void AGameStateGameplay::SetState_PostMatch()
{
}

void AGameStateGameplay::SetState(EGameplayGameState const State)
{
	using FStateFunc = void(AGameStateGameplay::*)();
	static constexpr FStateFunc Map[static_cast<unsigned long>(EGameplayGameState::Max)] = {
		&AGameStateGameplay::SetState_PreMatch,
		&AGameStateGameplay::SetState_PrePeriod,
		&AGameStateGameplay::SetState_PrePlay,
		&AGameStateGameplay::SetState_Play,
		&AGameStateGameplay::SetState_PostPlay,
		&AGameStateGameplay::SetState_PostPeriod,
		&AGameStateGameplay::SetState_PostMatch,
	};

	UE_LOG(LogTemp, Warning, TEXT("State changing from %d -> %d"), CurrentGameState, State);

	CurrentGameState = State;

	(this->*Map[static_cast<unsigned long>(State)])();

	StateChangeEvent.Broadcast(State);
}

void AGameStateGameplay::DelayedStateChange(EGameplayGameState const NewState, float const Delay)
{
	FTimerHandle Timer;
	GetWorld()->GetTimerManager().SetTimer(Timer, [&, NewState] { SetState(NewState); }, Delay, false);
}

void AGameStateGameplay::OnPeriodEnd()
{
	SetState(EGameplayGameState::PrePeriod);
}


bool AGameStateGameplay::IsState(EGameplayGameState const State) const
{
	return CurrentGameState == State;
}

EZone AGameStateGameplay::GetCurrentZone() const
{
	return CurrentZone;
}
