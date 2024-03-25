// Copyright 2024 Impending Technologies

#pragma once

#include "CoreMinimal.h"
#include "UI/Manager/Screen.h"
#include "ScreenPrePeriod.generated.h"

class UImage;
class UTextBlock;
/**
 *
 */
UCLASS()
class IMP023_API UScreenPrePeriod : public UScreen
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

protected:
	virtual void OnInputMain(int const PlayerIndex) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Period", meta = (AllowPrivateAccess = "true"))
	UTextBlock* TextPeriod;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Team", meta = (AllowPrivateAccess = "true"))
	UImage* ImageHome;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Team", meta = (AllowPrivateAccess = "true"))
	UImage* ImageAway1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Team", meta = (AllowPrivateAccess = "true"))
	UImage* ImageAway2;
};
