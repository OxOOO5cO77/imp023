// Copyright 2024 Impending Technologies

#pragma once

#include "CoreMinimal.h"
#include "UI/Manager/Screen.h"
#include "ScreenGameplayHud.generated.h"

class UImage;
class AGameStateGameplay;
class UProgressBar;
class UTextBlock;
/**
 *
 */
UCLASS()
class IMP023_API UScreenGameplayHud : public UScreen
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(FGeometry const& MyGeometry, float InDeltaTime) override;

private:
	void OnUpdateScores(TArray<int> const& Scores) const;
	void HandleDelayTimer();
	void HandlePeriodTimer() const;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Timer", meta = (AllowPrivateAccess = "true"))
	UTextBlock* TextDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Score", meta = (AllowPrivateAccess = "true"))
	UTextBlock* TextScoreHome;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Score", meta = (AllowPrivateAccess = "true"))
	UTextBlock* TextScoreAway1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Score", meta = (AllowPrivateAccess = "true"))
	UTextBlock* TextScoreAway2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Period", meta = (AllowPrivateAccess = "true"))
	UProgressBar* BarPeriod1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Period", meta = (AllowPrivateAccess = "true"))
	UProgressBar* BarPeriod2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Period", meta = (AllowPrivateAccess = "true"))
	UProgressBar* BarPeriod3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Team", meta = (AllowPrivateAccess = "true"))
	UImage* ImageLogoHome;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Team", meta = (AllowPrivateAccess = "true"))
	UImage* ImageLogoAway1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Team", meta = (AllowPrivateAccess = "true"))
	UImage* ImageLogoAway2;

private:
	UPROPERTY()
	AGameStateGameplay* GameState;

	FDelegateHandle OnUpdateScoresHandle;

	bool bDelayTimer;
};
