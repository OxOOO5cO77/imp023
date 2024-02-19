// Copyright 2024 Impending Technologies

#pragma once

#include "CoreMinimal.h"
#include "Component/CompZone.h"
#include "GameFramework/Actor.h"
#include "MinimapManager.generated.h"

UCLASS()
class IMP023_API AMinimapManager : public AActor
{
	GENERATED_BODY()

public:
	AMinimapManager();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	void OnChangeZone(EZone PreviousZone, EZone CurrentZone) const;

	static void SetCameraCaptureEnabled(ACameraActor const* const Camera, bool const bEnabled);

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Minimap Cameras", meta = (AllowPrivateAccess = "true"))
	TMap<EZone, ACameraActor*> Cameras;

private:
	FDelegateHandle OnChangeZoneHandle;
};
