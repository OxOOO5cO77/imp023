// Copyright 2024 Impending Technologies

#pragma once

#include "CoreMinimal.h"
#include "Component/CompZone.h"
#include "GameFramework/Actor.h"
#include "MinimapManager.generated.h"

class ASceneCapture2D;

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

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Minimap Captures", meta = (AllowPrivateAccess = "true"))
	TMap<EZone, ASceneCapture2D*> Minimaps;

private:
	FDelegateHandle OnChangeZoneHandle;
};
