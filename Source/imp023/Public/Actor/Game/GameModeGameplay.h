// Copyright 2024 Impending Technologies

#pragma once

#include "CoreMinimal.h"
#include "Component/CompZone.h"
#include "GameFramework/GameModeBase.h"
#include "GameModeGameplay.generated.h"

/**
 *
 */
UCLASS()
class IMP023_API AGameModeGameplay : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	void ResetActorsForZone(EZone const ZoneFrom, EZone const ZoneTo) const;

	UFUNCTION(BlueprintCallable)
	void HandlePossession(EZone const Zone) const;
};
