// Copyright 2024 Impending Technologies

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PlayerData.generated.h"

class UImage;

UENUM()
enum class EPlayerPosition
{
	Bench,
	Center,
	Defend,
	Attack1,
	Attack2,
	Frantic,
};


/**
 *
 */
UCLASS(BlueprintType)
class IMP023_API UPlayerData : public UDataAsset
{
	GENERATED_BODY()
public:
	virtual void GetAssetRegistryTags(TArray<FAssetRegistryTag>& OutTags) const override;

public:
	UPROPERTY(EditAnywhere)
	uint32 ID;
	UPROPERTY(EditAnywhere)
	FString Name;
	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UTexture2D> Image;
	UPROPERTY(EditAnywhere, AssetRegistrySearchable)
	EPlayerPosition Position;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, AssetRegistrySearchable, meta=(ClampMin=0.0f,ClampMax=1.0f,UIMin=0.0,UIMax=1.0f))
	float Rate;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, AssetRegistrySearchable, meta=(ClampMin=0.0f,ClampMax=1.0f,UIMin=0.0,UIMax=1.0f))
	float Power;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, AssetRegistrySearchable, meta=(ClampMin=0.0f,ClampMax=1.0f,UIMin=0.0,UIMax=1.0f))
	float Slide;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, AssetRegistrySearchable, meta=(ClampMin=0.0f,ClampMax=1.0f,UIMin=0.0,UIMax=1.0f))
	float Boing;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, AssetRegistrySearchable, meta=(ClampMin=0.0f,ClampMax=1.0f,UIMin=0.0,UIMax=1.0f))
	float Mass;

public:
	bool operator==(uint32_t const RHS) const;

public:
	float RateAsMaxVelocity() const;
	float PowerAsImpulse() const;
	float PowerAsBoost() const;
	float SlideAsFriction() const;
	float BoingAsRestitution() const;
	FString PositionAsString() const;

public:
	static int Attr(float const InValue);

};
