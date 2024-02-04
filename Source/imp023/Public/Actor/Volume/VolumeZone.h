// Copyright 2024 Impending Technologies

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerVolume.h"
#include "VolumeZone.generated.h"

class AGameStateGameplay;
class UCompZone;
/**
 *
 */
UCLASS()
class IMP023_API AVolumeZone : public ATriggerVolume
{
	GENERATED_BODY()

public:
	AVolumeZone();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnOverlap(AActor* OverlappedActor, AActor* OtherActor);

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Zone", meta = (AllowPrivateAccess = "true"))
	UCompZone* CompZone;

	UPROPERTY()
	AGameStateGameplay* GameState;
};
