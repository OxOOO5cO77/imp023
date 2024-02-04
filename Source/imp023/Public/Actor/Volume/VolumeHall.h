// Copyright 2024 Impending Technologies

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerVolume.h"
#include "VolumeHall.generated.h"

class ABall;
/**
 *
 */
UCLASS()
class IMP023_API AVolumeHall : public ATriggerVolume
{
	GENERATED_BODY()

public:
	AVolumeHall();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor);
	UFUNCTION()
	void OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor);

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Hall", meta = (AllowPrivateAccess = "true"))
	FVector Impulse;

	UPROPERTY()
	ABall* TrackedBall;
};
