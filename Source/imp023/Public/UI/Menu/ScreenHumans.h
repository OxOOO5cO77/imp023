// Copyright 2024 Impending Technologies

#pragma once

#include "CoreMinimal.h"
#include "UI/Manager/Screen.h"
#include "ScreenHumans.generated.h"

class UTextBlock;
/**
 *
 */
UCLASS()
class IMP023_API UScreenHumans : public UScreen
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

protected:
	virtual void OnInputMain(int const PlayerIndex) override;
	virtual void OnInputBack(int const PlayerIndex) override;
	virtual void OnInputLeft(int const PlayerIndex) override;
	virtual void OnInputRight(int const PlayerIndex) override;

private:
	void UpdateText() const;
	void WrapTrackedHumans(int const Amount);

private:
	UPROPERTY()
	UTextBlock* TextCount;
	UPROPERTY()
	UTextBlock* TextHuman;

	uint TrackedHumans;
};
