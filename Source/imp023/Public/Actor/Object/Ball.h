// Copyright 2024 Impending Technologies

#pragma once

#include "CoreMinimal.h"
#include "Actor/Gameplay/GameStateGameplay.h"
#include "GameFramework/Actor.h"
#include "Ball.generated.h"

class APlayerPawn;

UCLASS()
class IMP023_API ABall : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABall();

protected:
	virtual void BeginPlay() override;

public:
	void Boost(FVector const& Boost) const;
	FVector GetLocationTargetForBoost(FVector const& Source) const;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* CompStaticMeshBase;

private:
	void ResetBall();
	void OnStateChange(EGameplayGameState const State);
};
