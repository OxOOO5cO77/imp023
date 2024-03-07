// Copyright 2024 Impending Technologies

#pragma once

#include "CoreMinimal.h"
#include "PlayerData.h"
#include "Engine/DataAsset.h"
#include "TeamData.generated.h"

class UPlayerData;
/**
 *
 */
UCLASS()
class IMP023_API UTeamData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	uint32 ID;
	UPROPERTY(EditAnywhere)
	FString Name;
	UPROPERTY(EditAnywhere)
	FString Abbrev;
	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UTexture2D> Logo;
	UPROPERTY(EditAnywhere, meta=(HideAlphaChannel))
	FLinearColor Color;
	UPROPERTY(EditAnywhere, meta=(NoElementDuplicate))
	TArray<UPlayerData*> Players;

public:
	UPlayerData const* PlayerByPosition(EPlayerPosition const Position) const;

#if WITH_EDITOR

public:
	virtual EDataValidationResult IsDataValid(FDataValidationContext& Context) const override;

private:
	void Validate_PlayerCount(FDataValidationContext& Context, EDataValidationResult& Result) const;
	void Validate_PlayerValidCount(FDataValidationContext& Context, EDataValidationResult& Result) const;
	void Validate_PlayerPositions(FDataValidationContext& Context, EDataValidationResult& Result) const;

#endif
};
