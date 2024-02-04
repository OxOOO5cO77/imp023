// Copyright 2024 Impending Technologies

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerVolume.h"
#include "VolumeGoal.generated.h"

class AGameModeGameplay;
class UCompTeam;
class AGameStateGameplay;
/**
 *
 */
UCLASS()
class IMP023_API AVolumeGoal : public ATriggerVolume
{
	GENERATED_BODY()

public:
	AVolumeGoal();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnOverlap(AActor* OverlappedActor, AActor* OtherActor);

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Team", meta = (AllowPrivateAccess = "true"))
	UCompTeam* CompTeam;

	UPROPERTY()
	AGameStateGameplay* GameState;
};
