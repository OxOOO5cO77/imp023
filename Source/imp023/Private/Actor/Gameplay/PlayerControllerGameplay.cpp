// Copyright 2024 Impending Technologies

#include "Actor/Gameplay/PlayerControllerGameplay.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Actor/Menu/PlayerControllerMenu.h"
#include "Actor/Object/Ball.h"
#include "Actor/Player/PlayerPawn.h"
#include "Kismet/GameplayStatics.h"

void APlayerControllerGameplay::BeginPlay()
{
	Super::BeginPlay();

	if (ULocalPlayer const* LocalPlayer = Cast<ULocalPlayer>(Player))
	{
		if (UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (!InputMapping.IsNull())
			{
				InputSystem->AddMappingContext(InputMapping.LoadSynchronous(), 0);;
			}
		}
	}

	AActor* const Actor = UGameplayStatics::GetActorOfClass(GetWorld(), ABall::StaticClass());
	ABall* Ball = Cast<ABall>(Actor);

	SetViewTargetWithBlend(Ball);
}

void APlayerControllerGameplay::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInput = CastChecked<UEnhancedInputComponent>(InputComponent);
	check(EnhancedInput);

	EnhancedInput->BindAction(InputActionMove, ETriggerEvent::Triggered, this, &APlayerControllerGameplay::ActionMove);
	EnhancedInput->BindAction(InputActionBoost, ETriggerEvent::Started, this, &APlayerControllerGameplay::ActionBoost);
}

void APlayerControllerGameplay::ActionMove(FInputActionValue const& InputActionValue)
{
	APlayerPawn const* const PlayerPawn = Cast<APlayerPawn>(GetPawn());
	PlayerPawn->Move(InputActionValue.Get<FVector>());
}

void APlayerControllerGameplay::ActionBoost(FInputActionValue const& InputActionValue)
{
	APlayerPawn const* const PlayerPawn = Cast<APlayerPawn>(GetPawn());
	PlayerPawn->Boost();
}
