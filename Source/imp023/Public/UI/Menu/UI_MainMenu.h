// Copyright 2024 Impending Technologies

#pragma once

#include "CoreMinimal.h"
#include "UI/Manager/Screen.h"
#include "UI_MainMenu.generated.h"

class UButton;
/**
 *
 */
UCLASS()
class IMP023_API UUI_MainMenu : public UScreen
{
	GENERATED_BODY()

protected:
	virtual void OnInputMain(int const PlayerIndex) override;
};
