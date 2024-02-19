// Copyright 2024 Impending Technologies

#pragma once

#include "CoreMinimal.h"
#include "UI/Manager/Screen.h"
#include "ScreenGameplayHud.generated.h"

class UTextBlock;
/**
 *
 */
UCLASS()
class IMP023_API UScreenGameplayHud : public UScreen
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeDestruct() override;

private:
	void OnUpdateScores(TArray<int> const& Scores) const;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Score", meta = (AllowPrivateAccess = "true"))
	UTextBlock* TextScoreHome;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Score", meta = (AllowPrivateAccess = "true"))
	UTextBlock* TextScoreAway1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Score", meta = (AllowPrivateAccess = "true"))
	UTextBlock* TextScoreAway2;

private:
	FDelegateHandle OnUpdateScoresHandle;
};
