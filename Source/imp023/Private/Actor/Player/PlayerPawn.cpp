// Copyright 2024 Impending Technologies

#include "Actor/Player/PlayerPawn.h"

#include "Actor/Object/Ball.h"
#include "Actor/Game/GameStateGameplay.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CompStaticMeshBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Player Base"));
	RootComponent = CompStaticMeshBase;

	CompTeam = CreateDefaultSubobject<UCompTeam>(TEXT("Team"));
	CompLocator = CreateDefaultSubobject<UCompLocator>(TEXT("Locator"));
	CompZone = CreateDefaultSubobject<UCompZone>(TEXT("Zone"));
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	AActor* const Actor = UGameplayStatics::GetActorOfClass(GetWorld(), ABall::StaticClass());
	Ball = Cast<ABall>(Actor);

	CompStaticMeshBase->OnComponentHit.AddDynamic(this, &APlayerPawn::OnHit);
}

void APlayerPawn::Boost() const
{
	FVector const Dir = UKismetMathLibrary::GetDirectionUnitVector(GetActorLocation(), Ball->GetLocationTargetForBoost(this->GetActorLocation()));

	CompStaticMeshBase->SetPhysicsLinearVelocity(FVector::Zero());
	CompStaticMeshBase->AddImpulse(Dir * 1000.0f, NAME_None, true);
}

void APlayerPawn::Move(FVector const& Dir) const
{
	CompStaticMeshBase->AddImpulse(Dir * 10.0f, NAME_None, true);
}

void APlayerPawn::ResetTo(FVector const& Location)
{
	SetActorLocation(Location);
	CompStaticMeshBase->SetPhysicsLinearVelocity(FVector::Zero());
}

void APlayerPawn::InitComponents(EZone const Zone, ELocator const Locator, ETeam const Team) const
{
	CompZone->Set(Zone);
	CompLocator->Set(Locator);
	CompTeam->Set(Team);
}

void APlayerPawn::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, FHitResult const& Hit)
{
	// APlayerPawn const* const other = Cast<APlayerPawn>(OtherActor);
	// if (other)
	// {
	// 	UCompTeam const* const comp_team = Cast<UCompTeam>(other->GetComponentByClass(UCompTeam::StaticClass()));
	// 	ETeam const team = comp_team->Get();
	// 	UE_LOG(LogTemp, Warning, TEXT("Hit player on team: %d"), team);
	// }

	if (OtherActor == Ball)
	{
		AGameStateGameplay* const GameState = Cast<AGameStateGameplay>(UGameplayStatics::GetGameState(this));
		GameState->SetCurrentTeamTouched(CompTeam->Get());
	}
}
