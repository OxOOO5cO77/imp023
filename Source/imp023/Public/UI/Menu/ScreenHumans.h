// Copyright 2024 Impending Technologies

#pragma once

#include "CoreMinimal.h"
#include "UI/Manager/Screen.h"
#include "ScreenHumans.generated.h"

/**
 *
 */
UCLASS()
class IMP023_API UScreenHumans : public UScreen
{
	GENERATED_BODY()

protected:
	virtual void OnInputMain(int const PlayerIndex) override;
	virtual void OnInputBack(int const PlayerIndex) override;
};
