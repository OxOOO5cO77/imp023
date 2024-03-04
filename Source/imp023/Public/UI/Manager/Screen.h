// Copyright 2024 Impending Technologies

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Screen.generated.h"

class UScreenManager;
/**
 *
 */
UCLASS()
class IMP023_API UScreen : public UUserWidget
{
	GENERATED_BODY()

public:
	void Attach(UScreenManager* const Manager);

public:
	virtual void OnInputMain(int const ControllerIndex) {}
	virtual void OnInputAlt(int const ControllerIndex) {}
	virtual void OnInputBack(int const ControllerIndex) {}
	virtual void OnInputUp(int const ControllerIndex) {}
	virtual void OnInputDown(int const ControllerIndex) {}
	virtual void OnInputLeft(int const ControllerIndex) {}
	virtual void OnInputRight(int const ControllerIndex) {}

protected:
	UPROPERTY()
	UScreenManager* ScreenManager;
};
