// Copyright 2024 Impending Technologies

#include "Actor/Game/GameModeGameplay.h"

#include "Actor/Game/GameStateGameplay.h"
#include "Component/CompLocator.h"
#include "Component/CompTeam.h"
#include "Component/CompZone.h"
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


	AGameStateGameplay* GameState = Cast<AGameStateGameplay>(UGameplayStatics::GetGameState(this));
	check(GameState);

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

		ETeam const Team = FGameplayUtils::MapZoneLocatorToTeam(Zone, Zone, Locator);

		Player->InitComponents(Zone, Locator, Team);

		if (Zone == EZone::Middle)
		{
			PossessWithTeam(GameState, Player, Team);
		}
	}
}

void AGameModeGameplay::PossessWithTeam(AGameStateGameplay* const GameState, APlayerPawn* const Player, ETeam const Team)
{
	APlayerController* const Controller = GameState->GetPlayerControllerFromTeam(Team);

	if (Controller != nullptr)
	{
		Controller->bAutoManageActiveCameraTarget = false;
		Controller->Possess(Player);
	}
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

// static bool IsAtLocator(AActor const* const actor, ELocator const locator)
// {
// 	UCompLocator const* const locator_comp = Cast<UCompLocator>(actor->GetComponentByClass(UCompLocator::StaticClass()));
// 	return locator_comp->Get() == locator;
// }

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
			UE_LOG(LogTemp, Error, TEXT("ResetActorsForZone: start is null for %d->%d"), ZoneFrom, ZoneTo)
			continue;
		}

		UCompLocator const* const StartLoc = Cast<UCompLocator>(Start->GetComponentByClass(UCompLocator::StaticClass()));
		ETeam const Team = FGameplayUtils::MapZoneLocatorToTeam(ZoneFrom, ZoneTo, StartLoc->Get());

		if (Team == ETeam::None)
		{
			continue;
		}

		AActor** const Result = PlayersInZone.FindByPredicate([Team](AActor const* const Actor) { return IsOnTeam(Actor, Team); });
		if (Result == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("ResetActorsForZone: result is null for %d @ %d (total players in zone: %d)"), ZoneTo, Team, PlayersInZone.Num())
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
	ETeam constexpr Team = ETeam::Home;
	AActor** const Result = Players.FindByPredicate([Zone, Team](AActor const* const Actor) { return IsInZone(Actor, Zone) && IsOnTeam(Actor, Team); });

	if (Result == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("HandlePossession: result is null for %d @ %d (total: $d)"), Zone, Team, Players.Num())
		return;
	}

	APlayerPawn* const Player = Cast<APlayerPawn>(*Result);

	APlayerController* const Controller = GEngine->GetFirstLocalPlayerController(World);
	Controller->Possess(Player);
}
