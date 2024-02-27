// Copyright 2024 Impending Technologies

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CompTeam.generated.h"

UENUM(BlueprintType)
enum class ETeam : uint8
{
	None,
	Home,
	Away1,
	Away2,
};

DECLARE_MULTICAST_DELEGATE_OneParam(FUpdateTeamEvent, ETeam);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class IMP023_API UCompTeam : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UCompTeam();

public:
	FUpdateTeamEvent UpdateTeamEvent;

public:
	ETeam Get() const { return Team; }
	void Set(ETeam const Value);

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	ETeam Team;
};
