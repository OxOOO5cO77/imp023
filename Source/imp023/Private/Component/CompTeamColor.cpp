// Copyright 2024 Impending Technologies

#include "Component/CompTeamColor.h"

#include "Component/CompTeam.h"
#include "Data/TeamData.h"
#include "Subsystem/TeamStateSubsystem.h"

class UTeamStateSubsystem;
// Sets default values for this component's properties
UCompTeamColor::UCompTeamColor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UCompTeamColor::BeginPlay()
{
	Super::BeginPlay();

	AActor const* const OwningActor = GetOwner();
	UCompTeam* const CompTeam = CastChecked<UCompTeam>(OwningActor->GetComponentByClass(UCompTeam::StaticClass()));
	CompTeam->UpdateTeamEvent.AddUObject(this, &UCompTeamColor::SetTeamColor);

	SetTeamColor(CompTeam->Get());
}

void UCompTeamColor::SetTeamColor(ETeam const Team) const
{
	if( Team == ETeam::None)
	{
		return;
	}

	AActor const* const OwningActor = GetOwner();
	UStaticMeshComponent* const CompStaticMesh = CastChecked<UStaticMeshComponent>(OwningActor->GetComponentByClass(UStaticMeshComponent::StaticClass()));

	UTeamStateSubsystem const* const TeamStateSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UTeamStateSubsystem>();
	UTeamData const* const TeamData = TeamStateSubsystem->GetTeam(Team);

	UMaterialInstanceDynamic* Material = CompStaticMesh->CreateDynamicMaterialInstance(0);
	Material->SetVectorParameterValue("TeamColor", TeamData->Color);
	CompStaticMesh->SetMaterial(0, Material);
}
