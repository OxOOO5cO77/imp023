// Copyright 2024 Impending Technologies

#include "Actor/Gameplay/GameModeGameplay.h"

#include "Actor/Gameplay/GameStateGameplay.h"
#include "Enum/ELocator.h"
#include "Enum/ETeam.h"
#include "Enum/EZone.h"
#include "Utils/GameplayUtils.h"
#include "Actor/Player/PlayerPawn.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"

void AGameModeGameplay::BeginPlay()
{
	Super::BeginPlay();

	UWorld* const World = GetWorld();
	TArray<AActor*> Starts;
	UGameplayStatics::GetAllActorsOfClass(World, APlayerStart::StaticClass(), Starts);

	AGameStateGameplay* GameStateGameplay = GetGameState<AGameStateGameplay>();
	check(GameStateGameplay);

	OnChangeZoneHandle = GameStateGameplay->ChangeZoneEvent.AddUObject(this, &AGameModeGameplay::OnChangeZone);

	for (AActor const* Start : Starts)
	{
		UCompLocator const* const StartLocator = Cast<UCompLocator>(Start->GetComponentByClass(UCompLocator::StaticClass()));
		ELocator const Locator = StartLocator->Get();
		UCompZone const* const StartZone = Cast<UCompZone>(Start->GetComponentByClass(UCompZone::StaticClass()));
		EZone const Zone = StartZone->Get();

		if (Locator == ELocator::South && Zone == EZone::Middle)
		{
			continue;
		}


		APlayerPawn* const Player = Cast<APlayerPawn>(World->SpawnActor(DefaultPawnClass, &Start->GetActorTransform()));

		ETeam const Team = FGameplayUtils::MapZoneLocatorToTeamPeriod(Zone, Zone, Locator, GameStateGameplay->Period);

		Player->InitComponents(Zone, Locator, Team);

		if (Zone == EZone::Middle)
		{
			PossessWithTeam(GameStateGameplay, Player, Team);
		}
	}
}

void AGameModeGameplay::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	AGameStateGameplay* GameStateGameplay = GetGameState<AGameStateGameplay>();
	check(GameStateGameplay);

	GameStateGameplay->ChangeZoneEvent.Remove(OnChangeZoneHandle);
}

void AGameModeGameplay::PossessWithTeam(AGameStateGameplay* const GameStateGameplay, APlayerPawn* const Player, ETeam const Team)
{
	APlayerController* const Controller = GameStateGameplay->GetPlayerControllerFromTeam(Team);

	if (Controller != nullptr)
	{
		Controller->bAutoManageActiveCameraTarget = false;
		Controller->Possess(Player);
	}
}

void AGameModeGameplay::OnChangeZone(EZone const PreviousZone, EZone const CurrentZone) const
{
	ResetActorsForZone(CurrentZone, PreviousZone);	// reset players in the leaving zone (PreviousZone) as if the ball was coming from the new zone (CurrentZone)
	HandlePossession(CurrentZone);
}

static bool IsInZone(AActor const* const Actor, EZone const Zone)
{
	if (Actor == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("IsInZone: Actor is null for %d"), Zone)
		return false;
	}
	UCompZone const* const CompZone = Cast<UCompZone>(Actor->GetComponentByClass(UCompZone::StaticClass()));
	return CompZone->Get() == Zone;
}

static bool IsOnTeam(AActor const* const Actor, ETeam const Team)
{
	if (Actor == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("IsOnTeam: Actor is null for %d"), Team)
		return false;
	}
	UCompTeam const* const CompTeam = Cast<UCompTeam>(Actor->GetComponentByClass(UCompTeam::StaticClass()));
	return CompTeam->Get() == Team;
}

void AGameModeGameplay::ResetActorsForAllZones() const
{
	UWorld const* World = GetWorld();

	TArray<AActor*> Starts;
	UGameplayStatics::GetAllActorsOfClass(World, APlayerStart::StaticClass(), Starts);

	TArray<AActor*> Players;
	UGameplayStatics::GetAllActorsOfClass(World, APlayerPawn::StaticClass(), Players);

	for (AActor const* Start : Starts)
	{
		UCompZone const* const StartZone = Cast<UCompZone>(Start->GetComponentByClass(UCompZone::StaticClass()));
		EZone const Zone = StartZone->Get();

		UCompLocator const* const StartLoc = Cast<UCompLocator>(Start->GetComponentByClass(UCompLocator::StaticClass()));
		ETeam const Team = FGameplayUtils::MapZoneLocatorToTeamPeriod(Zone, Zone, StartLoc->Get(), GetGameState<AGameStateGameplay>()->Period);

		if (Team == ETeam::None)
		{
			continue;
		}

		AActor** const Result = Players.FindByPredicate([Zone,Team](AActor const* const PlayerPawn) -> bool { return IsOnTeam(PlayerPawn, Team) && IsInZone(PlayerPawn, Zone); });
		if (Result == nullptr)
		{
			continue;
		}

		APlayerPawn* const Player = Cast<APlayerPawn>(*Result);
		Player->ResetTo(Start->GetActorLocation());
	}
}

void AGameModeGameplay::ResetActorsForZone(EZone const ZoneFrom, EZone const ZoneTo) const
{
	UWorld const* World = GetWorld();

	TArray<AActor*> Starts;
	UGameplayStatics::GetAllActorsOfClass(World, APlayerStart::StaticClass(), Starts);
	TArray<AActor*> StartsInZone = Starts.FilterByPredicate([ZoneTo](AActor const* const Actor) { return IsInZone(Actor, ZoneTo); });

	TArray<AActor*> Players;
	UGameplayStatics::GetAllActorsOfClass(World, APlayerPawn::StaticClass(), Players);
	TArray<AActor*> PlayersInZone = Players.FilterByPredicate([ZoneTo](AActor const* const Actor) { return IsInZone(Actor, ZoneTo); });

	for (AActor const* Start : StartsInZone)
	{
		if (Start == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("ResetActorsForZone: start is null for %d->%d"), ZoneFrom, ZoneTo);
			continue;
		}

		UCompLocator const* const StartLoc = Cast<UCompLocator>(Start->GetComponentByClass(UCompLocator::StaticClass()));
		ETeam const Team = FGameplayUtils::MapZoneLocatorToTeamPeriod(ZoneFrom, ZoneTo, StartLoc->Get(), GetGameState<AGameStateGameplay>()->Period);

		if (Team == ETeam::None)
		{
			continue;
		}

		AActor** const Result = PlayersInZone.FindByPredicate([Team](AActor const* const Actor) { return IsOnTeam(Actor, Team); });
		if (Result == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("ResetActorsForZone: result is null for %d @ %d (total players in zone: %d)"), ZoneTo, Team, PlayersInZone.Num());
			continue;
		}

		APlayerPawn* const Player = Cast<APlayerPawn>(*Result);
		Player->ResetTo(Start->GetActorLocation());
	}
}

void AGameModeGameplay::HandlePossession(EZone const Zone) const
{
	UWorld const* World = GetWorld();
	TArray<AActor*> Players;
	UGameplayStatics::GetAllActorsOfClass(World, APlayerPawn::StaticClass(), Players);

	TArray<AActor*> FilteredPlayers = Players.FilterByPredicate([Zone](AActor const* const Actor) { return IsInZone(Actor, Zone); });

	AGameStateGameplay* const GameStateGameplay = GetGameState<AGameStateGameplay>();
	check(GameStateGameplay);

	for (AActor* FilteredPlayer : FilteredPlayers)
	{
		APlayerPawn* const Player = Cast<APlayerPawn>(FilteredPlayer);
		PossessWithTeam(GameStateGameplay, Player, Player->GetTeam());
	}
}
