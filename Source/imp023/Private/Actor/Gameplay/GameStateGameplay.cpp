// Copyright 2024 Impending Technologies

#include "Actor/Gameplay/GameStateGameplay.h"

#include "Actor/Gameplay/GameModeGameplay.h"
#include "Actor/Gameplay/PlayerStateGameplay.h"
#include "Kismet/GameplayStatics.h"
#include "Subsystem/TeamStateSubsystem.h"
#include "Utils/GameplayUtils.h"

float constexpr GSecondsPerPeriod = 90.0f;

void AGameStateGameplay::BeginPlay()
{
	Super::BeginPlay();

	check(BPScreenManager);
	ScreenManager = NewObject<UScreenManager>(this, BPScreenManager);;
	check(ScreenManager);

	SetState(EGameplayGameState::PreMatch);
}

void AGameStateGameplay::ChangeZone(EZone const Zone)
{
	PreviousZone = CurrentZone;
	CurrentZone = Zone;

	ChangeZoneEvent.Broadcast(PreviousZone, CurrentZone);
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

	BroadcastScores();

	SetState(EGameplayGameState::PostPlay);
}

void AGameStateGameplay::BroadcastScores() const
{
	UpdateScoresEvent.Broadcast(Score);
}

void AGameStateGameplay::ResetGameplay()
{
	PreviousZone = EZone::Middle;
	CurrentZone = EZone::Middle;

	PreviousTeamTouched = ETeam::None;
	CurrentTeamTouched = ETeam::None;

	AGameModeGameplay const* const GameMode = Cast<AGameModeGameplay>(UGameplayStatics::GetGameMode(this));
	GameMode->ResetActorsForAllZones();
}

void AGameStateGameplay::SetState_PreMatch()
{
	Period = 0;
	Score.Init(0, 4);

	ScreenManager->NavigateTo("PreMatch");
}

void AGameStateGameplay::SetState_PrePeriod()
{
	Period += 1;

	FTimerManager& TM = GetWorld()->GetTimerManager();
	TM.SetTimer(TimerPeriod, [&] { SetState(EGameplayGameState::PostPeriod); }, GSecondsPerPeriod, false);
	TM.PauseTimer(TimerPeriod);

	ScreenManager->NavigateTo("PrePeriod");
}

void AGameStateGameplay::SetState_PrePlay()
{
	GetWorld()->GetTimerManager().PauseTimer(TimerPeriod);
	ResetGameplay();

	ScreenManager->NavigateTo("HUD");
	DelayedStateChange(EGameplayGameState::Play, 3.0f);
}

void AGameStateGameplay::SetState_Play()
{
	GetWorld()->GetTimerManager().UnPauseTimer(TimerPeriod);
}

void AGameStateGameplay::SetState_PostPlay()
{
	GetWorld()->GetTimerManager().PauseTimer(TimerPeriod);

	ScreenManager->NavigateTo("Goal");

	DelayedStateChange(EGameplayGameState::PrePlay, 3.0f);
}

void AGameStateGameplay::SetState_PostPeriod()
{
	ScreenManager->NavigateTo("PostPeriod");;
}

void AGameStateGameplay::SetState_PostMatch()
{
	ScreenManager->NavigateTo("PostMatch");
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

static bool PlayerStateGameplayIsTeam(APlayerState* const PlayerState, ETeam const Team)
{
	APlayerStateGameplay const* const PlayerStateGameplay = Cast<APlayerStateGameplay const>(PlayerState);
	return PlayerStateGameplay != nullptr && PlayerStateGameplay->Team == Team;
}

APlayerController* AGameStateGameplay::GetPlayerControllerFromTeam(ETeam const Team)
{
	using namespace std::placeholders;
	TObjectPtr<APlayerState> const* const PlayerState = PlayerArray.FindByPredicate(std::bind(&PlayerStateGameplayIsTeam, _1, Team));
	if (PlayerState != nullptr)
	{
		return (*PlayerState)->GetPlayerController();
	}
	return nullptr;
}

void AGameStateGameplay::ProcessInputMain(APlayerControllerGameplay* PlayerControllerGameplay) const
{
	ScreenManager->HandleInputMain(0);	// ignore which player clicked for now
}

float AGameStateGameplay::GetTimerDelayRemaining() const
{
	return GetWorld()->GetTimerManager().GetTimerRemaining(TimerDelay);
}

float AGameStateGameplay::GetPeriodTimeRemainingPercent() const
{
	return GetWorld()->GetTimerManager().GetTimerRemaining(TimerPeriod) / GSecondsPerPeriod;
}

void AGameStateGameplay::DelayedStateChange(EGameplayGameState const NewState, float const Delay)
{
	GetWorld()->GetTimerManager().SetTimer(TimerDelay, [&, NewState] { SetState(NewState); }, Delay, false);
}

bool AGameStateGameplay::IsState(EGameplayGameState const State) const
{
	return CurrentGameState == State;
}

EZone AGameStateGameplay::GetCurrentZone() const
{
	return CurrentZone;
}

FLinearColor AGameStateGameplay::GetTeamColorForPeriod(ETeam const Team) const
{
	UTeamStateSubsystem const* const TeamStateSubsystem = UGameplayStatics::GetGameInstance(this)->GetSubsystem<UTeamStateSubsystem>();
	check(TeamStateSubsystem);
	return TeamStateSubsystem->GetColor(FGameplayUtils::MapPeriodTeamToTeam(Period, Team));
}
