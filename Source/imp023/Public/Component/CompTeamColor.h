// Copyright 2024 Impending Technologies

#pragma once

#include "CoreMinimal.h"
#include "CompTeam.h"
#include "Components/ActorComponent.h"
#include "CompTeamColor.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class IMP023_API UCompTeamColor : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UCompTeamColor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	void SetTeamColor(ETeam const Team) const;
};
