// Copyright 2024 Impending Technologies

#pragma once

#include "CoreMinimal.h"
#include "Enum/ETeam.h"
#include "GameFramework/PlayerState.h"
#include "PlayerStateMenu.generated.h"

/**
 *
 */
UCLASS()
class IMP023_API APlayerStateMenu : public APlayerState
{
	GENERATED_BODY()

public:
	APlayerStateMenu();
	virtual void CopyProperties(APlayerState* PlayerState) override;

public:
	ETeam Team;
};
