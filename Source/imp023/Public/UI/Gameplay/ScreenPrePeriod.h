// Copyright 2024 Impending Technologies

#pragma once

#include "CoreMinimal.h"
#include "UI/Manager/Screen.h"
#include "ScreenPrePeriod.generated.h"

/**
 *
 */
UCLASS()
class IMP023_API UScreenPrePeriod : public UScreen
{
	GENERATED_BODY()

protected:
	virtual void OnInputMain(int const PlayerIndex) override;
};
