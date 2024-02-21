// Copyright 2024 Impending Technologies

#pragma once

#include "CoreMinimal.h"
#include "Component/CompTeam.h"
#include "GameFramework/PlayerState.h"
#include "PlayerStateGameplay.generated.h"

/**
 *
 */
UCLASS()
class IMP023_API APlayerStateGameplay : public APlayerState
{
	GENERATED_BODY()

public:
	APlayerStateGameplay();

public:
	ETeam Team;
};
