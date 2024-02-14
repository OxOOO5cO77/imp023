// Copyright 2024 Impending Technologies

#pragma once

#include "CoreMinimal.h"
#include "Screen.h"
#include "UI_PlayerSelect.generated.h"

class UTextBlock;
/**
 *
 */
UCLASS()
class IMP023_API UUI_PlayerSelect : public UScreen
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;
	virtual void OnInputMain(int const PlayerIndex) override;
	virtual void OnInputAlt(int PlayerIndex) override;
	virtual void OnInputBack(int const PlayerIndex) override;

private:
	void Advance(int const PlayerIndex, bool const IsHuman);
	TWeakObjectPtr<UTextBlock> TextFromSlot(uint const SlotIndex) const;

private:
	UPROPERTY()
	UTextBlock* TextHome;
	UPROPERTY()
	UTextBlock* TextAway1;
	UPROPERTY()
	UTextBlock* TextAway2;

	uint TrackedSlotIndex;
};
