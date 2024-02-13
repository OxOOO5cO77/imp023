// Copyright 2024 Impending Technologies

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI_MainMenu.generated.h"

class UButton;
/**
 *
 */
UCLASS()
class IMP023_API UUI_MainMenu : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;

private:
	UFUNCTION()
	void OnClickGo();

private:
	UPROPERTY()
	UButton* ButtonGo;
};