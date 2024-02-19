// Copyright 2024 Impending Technologies

#pragma once

#include "CoreMinimal.h"
#include "UI/Manager/Screen.h"
#include "ScreenPostPeriod.generated.h"

/**
 *
 */
UCLASS()
class IMP023_API UScreenPostPeriod : public UScreen
{
	GENERATED_BODY()

protected:
	virtual void OnInputMain(int const PlayerIndex) override;
};
