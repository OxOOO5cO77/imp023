// Copyright 2024 Impending Technologies

#pragma once

#include "CoreMinimal.h"
#include "Actor/Gameplay/GameStateGameplay.h"
#include "Components/ActorComponent.h"
#include "CompTeamPeriodChange.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class IMP023_API UCompTeamPeriodChange : public UActorComponent
{
	GENERATED_BODY()

public:
	UCompTeamPeriodChange();

protected:
	virtual void BeginPlay() override;

private:
	void OnStateChange(EGameplayGameState const GameplayGameState) const;

private:
	UPROPERTY()
	UCompTeam* CompTeam;
};
