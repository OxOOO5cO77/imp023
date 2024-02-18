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
	void HandleInputMain(int const Idx);
	void HandleInputAlt(int const Idx);
	void HandleInputBack(int const Idx);

protected:
	virtual void OnInputMain(int const Idx);
	virtual void OnInputAlt(int const Idx);
	virtual void OnInputBack(int const Idx);

protected:
	UPROPERTY()
	UScreenManager* ScreenManager;
};
