// Copyright 2024 Impending Technologies

#pragma once

#include "CoreMinimal.h"
#include "UI/Manager/Screen.h"
#include "ScreenPreMatch.generated.h"

class UTextBlock;
class UImage;
/**
 *
 */
UCLASS()
class IMP023_API UScreenPreMatch : public UScreen
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;
	virtual void OnInputMain(int const PlayerIndex) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Team", meta = (AllowPrivateAccess = "true"))
	UImage* ImageHome;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Team", meta = (AllowPrivateAccess = "true"))
	UTextBlock* TextHome;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Team", meta = (AllowPrivateAccess = "true"))
	UImage* ImageAway1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Team", meta = (AllowPrivateAccess = "true"))
	UTextBlock* TextAway1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Team", meta = (AllowPrivateAccess = "true"))
	UImage* ImageAway2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Team", meta = (AllowPrivateAccess = "true"))
	UTextBlock* TextAway2;
};
