// Copyright 2024 Impending Technologies

#pragma once

#include "CoreMinimal.h"
#include "Enum/ETeam.h"
#include "Enum/EZone.h"
#include "GameFramework/GameModeBase.h"
#include "GameModeGameplay.generated.h"

class AGameStateGameplay;
class APlayerPawn;
/**
 *
 */
UCLASS()
class IMP023_API AGameModeGameplay : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	static void PossessWithTeam(AGameStateGameplay* const GameStateGameplay, APlayerPawn* const Player, ETeam const Team);
	void OnChangeZone(EZone const PreviousZone, EZone const CurrentZone) const;

public:
	void ResetActorsForAllZones() const;
	void ResetActorsForZone(EZone const ZoneFrom, EZone const ZoneTo) const;
	void HandlePossession(EZone const Zone) const;

private:
	FDelegateHandle OnChangeZoneHandle;

};
