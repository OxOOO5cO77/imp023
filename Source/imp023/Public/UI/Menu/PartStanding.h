// Copyright 2024 Impending Technologies

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Subsystem/LeagueSubsystem.h"
#include "PartStanding.generated.h"

class UTextBlock;
class UImage;
/**
 *
 */
UCLASS()
class IMP023_API UPartStanding : public UUserWidget
{
	GENERATED_BODY()

public:
	void Setup(FLeagueTeam const* const LeagueTeam, FText const& RankText) const;

private:
	UPROPERTY()
	UTextBlock* TextRank;

	UPROPERTY()
	UImage* ImageTeam;

	UPROPERTY()
	UTextBlock* TextGP;
	UPROPERTY()
	UTextBlock* TextW;
	UPROPERTY()
	// ReSharper disable once CppUE4CodingStandardNamingViolationWarning
	UTextBlock* TextSW;
	UPROPERTY()
	UTextBlock* TextD;
	UPROPERTY()
	UTextBlock* TextSL;
	UPROPERTY()
	UTextBlock* TextL;

	UPROPERTY()
	UTextBlock* TextPts;
};
