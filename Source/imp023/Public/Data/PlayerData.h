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
UCLASS()
class IMP023_API UPlayerData : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	uint32 ID;
	UPROPERTY(EditAnywhere)
	FString Name;
	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UTexture2D> Image;
	UPROPERTY(EditAnywhere)
	EPlayerPosition Position;
	UPROPERTY(EditAnywhere, meta=(ClampMin=0.0f,ClampMax=1.0f,UIMin=0.0,UIMax=1.0f))
	float Rate;
	UPROPERTY(EditAnywhere, meta=(ClampMin=0.0f,ClampMax=1.0f,UIMin=0.0,UIMax=1.0f))
	float Power;
	UPROPERTY(EditAnywhere, meta=(ClampMin=0.0f,ClampMax=1.0f,UIMin=0.0,UIMax=1.0f))
	float Slide;
	UPROPERTY(EditAnywhere, meta=(ClampMin=0.0f,ClampMax=1.0f,UIMin=0.0,UIMax=1.0f))
	float Boing;
	UPROPERTY(EditAnywhere, meta=(ClampMin=0.0f,ClampMax=1.0f,UIMin=0.0,UIMax=1.0f))
	float Mass;

public:
	bool operator==(uint32_t const RHS) const;

public:
	float RateAsMaxVelocity() const;
	float PowerAsImpulse() const;
	float PowerAsBoost() const;
	float SlideAsFriction() const;
	float BoingAsRestitution() const;

public:
	static int Attr(float const InValue);

};
