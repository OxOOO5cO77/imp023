// Copyright 2024 Impending Technologies

// ReSharper disable CppUE4CodingStandardNamingViolationWarning
#pragma once

#include "CoreMinimal.h"
#include "UI/Manager/Screen.h"
#include "ScreenStandings.generated.h"

class UPartStanding;
/**
 *
 */
UCLASS()
class IMP023_API UScreenStandings : public UScreen
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual void OnInputMain(int const PlayerIndex) override;

private:
	UPartStanding const* Part(uint32 Index) const;

private:
	UPROPERTY()
	UPartStanding* Team1st;
	UPROPERTY()
	UPartStanding* Team2nd;
	UPROPERTY()
	UPartStanding* Team3rd;
	UPROPERTY()
	UPartStanding* Team4th;
	UPROPERTY()
	UPartStanding* Team5th;
	UPROPERTY()
	UPartStanding* Team6th;
	UPROPERTY()
	UPartStanding* Team7th;
	UPROPERTY()
	UPartStanding* Team8th;
};
