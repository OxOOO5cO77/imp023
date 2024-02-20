// Copyright 2024 Impending Technologies


#include "Actor/Manager/MinimapManager.h"

#include "Actor/Gameplay/GameStateGameplay.h"
#include "Camera/CameraActor.h"
#include "Component/CompZone.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AMinimapManager::AMinimapManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AMinimapManager::BeginPlay()
{
	Super::BeginPlay();

	AGameStateGameplay* GameState = CastChecked<AGameStateGameplay>(UGameplayStatics::GetGameState(this));

	OnChangeZoneHandle = GameState->ChangeZoneEvent.AddUObject(this, &AMinimapManager::OnChangeZone);
}

void AMinimapManager::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	AGameStateGameplay* GameState = CastChecked<AGameStateGameplay>(UGameplayStatics::GetGameState(this));

	GameState->ChangeZoneEvent.Remove(OnChangeZoneHandle);
}

void AMinimapManager::OnChangeZone(EZone const PreviousZone, EZone const CurrentZone) const
{
	for (auto const& Camera : Cameras)
	{
		SetCameraCaptureEnabled(Camera.Value, Camera.Key == CurrentZone);
	}
}

void AMinimapManager::SetCameraCaptureEnabled(ACameraActor const* const Camera, bool const bEnabled)
{
	USceneCaptureComponent2D* Component = Cast<USceneCaptureComponent2D>(Camera->GetComponentByClass(USceneCaptureComponent2D::StaticClass()));
	Component->SetVisibleFlag(bEnabled);
}
