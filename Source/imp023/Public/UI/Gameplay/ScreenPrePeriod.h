// Copyright 2024 Impending Technologies

#pragma once

#include "CoreMinimal.h"
#include "UI/Manager/Screen.h"
#include "ScreenPrePeriod.generated.h"

class UTextBlock;
/**
 *
 */
UCLASS()
class IMP023_API UScreenPrePeriod : public UScreen
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;

protected:
	virtual void OnInputMain(int const PlayerIndex) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Period", meta = (AllowPrivateAccess = "true"))
	UTextBlock* TextPeriod;
};
