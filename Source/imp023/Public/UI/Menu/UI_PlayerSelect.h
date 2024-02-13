// Copyright 2024 Impending Technologies

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI_PlayerSelect.generated.h"

class UTextBlock;
/**
 *
 */
UCLASS()
class IMP023_API UUI_PlayerSelect : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeOnInitialized() override;

private:
	UPROPERTY()
	UTextBlock* TextHome;
	UPROPERTY()
	UTextBlock* TextAway1;
	UPROPERTY()
	UTextBlock* TextAway2;
};
