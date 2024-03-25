// Copyright 2024 Impending Technologies

#pragma once

#include "CoreMinimal.h"
#include "UI/Manager/Screen.h"
#include "ScreenGoal.generated.h"

class UHorizontalBox;
class UImage;
class UTextBlock;

/**
 *
 */
UCLASS()
class IMP023_API UScreenGoal : public UScreen
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

protected:
	virtual void OnInputMain(int PlayerIndex) override;

private:
	UPROPERTY()
	UTextBlock* TextGoalTitle;
	UPROPERTY()
	UHorizontalBox* BoxGoal;
	UPROPERTY()
	UTextBlock* TextGoalPlayer;
	UPROPERTY()
	UTextBlock* TextGoalTeam;

	UPROPERTY()
	UHorizontalBox* BoxOwnGoal;
	UPROPERTY()
	UTextBlock* TextOwnGoalPlayer;
	UPROPERTY()
	UTextBlock* TextOwnGoalTeam;

	UPROPERTY()
	UTextBlock* TextTimeOfGoal;

	UPROPERTY()
	UImage* ImageGoalPlayer;
};
