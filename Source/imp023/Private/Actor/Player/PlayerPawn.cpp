// Copyright 2024 Impending Technologies

#include "Actor/Player/PlayerPawn.h"

#include "Actor/Gameplay/GameStateGameplay.h"
#include "Actor/Object/Ball.h"
#include "Component/CompTeamColor.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Subsystem/TeamStateSubsystem.h"
#include "Utils/GameplayUtils.h"

// Sets default values
APlayerPawn::APlayerPawn()
	: PlayerData(nullptr)
	  , BoostLimiter(0.0f)
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CompStaticMeshBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Player Base"));
	RootComponent = CompStaticMeshBase;

	CompTeam = CreateDefaultSubobject<UCompTeam>(TEXT("Team"));
	CompLocator = CreateDefaultSubobject<UCompLocator>(TEXT("Locator"));
	CompZone = CreateDefaultSubobject<UCompZone>(TEXT("Zone"));
	CompTeamColor = CreateDefaultSubobject<UCompTeamColor>(TEXT("Team Color"));
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	AActor* const Actor = UGameplayStatics::GetActorOfClass(GetWorld(), ABall::StaticClass());
	Ball = Cast<ABall>(Actor);
}

void APlayerPawn::Tick(float const DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (BoostLimiter > 0.0f)
	{
		BoostLimiter -= DeltaSeconds;
	}
}

float GBoostLimiter = 0.5f;

void APlayerPawn::Boost()
{
	if (BoostLimiter <= 0.0f)
	{
		FVector const VecToBall = UKismetMathLibrary::GetDirectionUnitVector(GetActorLocation(), Ball->GetActorLocation());
		FVector const VecToTarget = UKismetMathLibrary::GetDirectionUnitVector(GetActorLocation(), Ball->GetLocationTargetForBoost(this->GetActorLocation()));

		float const DotProduct = UKismetMathLibrary::Dot_VectorVector(VecToBall, VecToTarget);
		FVector const& Target = DotProduct > 0 ? VecToTarget : VecToBall;

		CompStaticMeshBase->SetPhysicsLinearVelocity(Target * PlayerData->PowerAsBoost());
		BoostLimiter = GBoostLimiter;
	}
}

void APlayerPawn::Move(FVector const& Dir) const
{
	FVector const OldVelocity = CompStaticMeshBase->GetPhysicsLinearVelocity();
	float const CurRate = OldVelocity.Length();
	float const MaxRate = PlayerData->RateAsMaxVelocity();
	float const Impulse = PlayerData->PowerAsImpulse();

	CompStaticMeshBase->AddImpulse(Dir * Impulse, NAME_None, true);
	FVector const NewVelocity = CompStaticMeshBase->GetPhysicsLinearVelocity();
	FVector const ClampedVelocity = NewVelocity.GetClampedToMaxSize( CurRate > MaxRate ? CurRate : MaxRate);;
	CompStaticMeshBase->SetPhysicsLinearVelocity(ClampedVelocity);
}

void APlayerPawn::ResetTo(FVector const& Location)
{
	SetActorLocation(Location);
	CompStaticMeshBase->SetPhysicsLinearVelocity(FVector::Zero());
}

ETeam APlayerPawn::GetTeam() const
{
	return CompTeam->Get();
}

void APlayerPawn::InitComponents(EZone const Zone, ELocator const Locator, ETeam const Team)
{
	CompZone->Set(Zone);
	CompLocator->Set(Locator);
	CompTeam->Set(Team);

	UTeamStateSubsystem const* const TeamStateSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UTeamStateSubsystem>();
	EPlayerPosition const PlayerPosition = FGameplayUtils::MapZoneTeamToPlayerPosition(Zone, Team);
	PlayerData = TeamStateSubsystem->GetTeamPlayer(Team, PlayerPosition);

	UPhysicalMaterial* const PhysicalMaterial = CreateMaterialFromPlayer(PlayerData);
	CompStaticMeshBase->SetPhysMaterialOverride(PhysicalMaterial);
	CompStaticMeshBase->OnComponentHit.AddDynamic(this, &APlayerPawn::OnHit);
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
		AGameStateGameplay* const GameState = GetWorld()->GetGameState<AGameStateGameplay>();
		GameState->SetCurrentTouched(PlayerData, CompTeam->Get());
	}
}

UPhysicalMaterial* APlayerPawn::CreateMaterialFromPlayer(UPlayerData const* const PlayerData)
{
	UPhysicalMaterial* PhysicalMaterial = NewObject<UPhysicalMaterial>();

	PhysicalMaterial->RaiseMassToPower = PlayerData->Mass;
	PhysicalMaterial->Friction = PlayerData->SlideAsFriction();
	PhysicalMaterial->StaticFriction = PlayerData->SlideAsFriction();
	PhysicalMaterial->bOverrideFrictionCombineMode = false;
	PhysicalMaterial->Restitution = PlayerData->BoingAsRestitution();
	PhysicalMaterial->bOverrideRestitutionCombineMode = false;

	PhysicalMaterial->AddToRoot();

	return PhysicalMaterial;
}
