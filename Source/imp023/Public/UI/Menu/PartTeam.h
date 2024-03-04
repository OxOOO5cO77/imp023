// Copyright 2024 Impending Technologies

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PartTeam.generated.h"

class UTeamData;
class UTextBlock;
class UImage;
/**
 *
 */
UCLASS()
class IMP023_API UPartTeam : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetLogo(UTeamData const* const TeamData) const;
	void SetSelectedColor(FLinearColor const& Color) const;
	void SetText(FString const& Text) const;

private:
	UPROPERTY()
	UTextBlock* TextTeam;

	UPROPERTY()
	UImage* ImageTeam;

	UPROPERTY()
	UImage* ImageSelectTeam;
};
