// Copyright 2024 Impending Technologies

#pragma once

#include "CoreMinimal.h"
#include "Component/CompLocator.h"
#include "Component/CompTeam.h"
#include "Component/CompZone.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

class ABall;

UCLASS()
class IMP023_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	APlayerPawn();

protected:
	virtual void BeginPlay() override;

public:
	void InitComponents(EZone const Zone, ELocator const Locator, ETeam const Team) const;

public:
	void Boost() const;
	void Move(FVector const& Dir) const;
	void ResetTo(FVector const& Location);

	ETeam GetTeam() const;

private:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, FHitResult const& Hit);

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* CompStaticMeshBase;

	UPROPERTY(EditAnywhere, Category="Team", meta = (AllowPrivateAccess = "true"))
	UCompTeam* CompTeam;
	UPROPERTY(EditAnywhere, Category="Team", meta = (AllowPrivateAccess = "true"))
	UCompLocator* CompLocator;
	UPROPERTY(EditAnywhere, Category="Team", meta = (AllowPrivateAccess = "true"))
	UCompZone* CompZone;

	UPROPERTY()
	ABall* Ball;
};
