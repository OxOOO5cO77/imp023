// Copyright 2024 Impending Technologies

#pragma once

#include "CoreMinimal.h"
#include "Screen.h"
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
	virtual void NativeOnInitialized() override;
	virtual void OnInputMain(int const PlayerIndex) override;
};
