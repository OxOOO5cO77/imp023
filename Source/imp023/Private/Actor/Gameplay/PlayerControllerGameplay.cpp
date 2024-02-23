// Copyright 2024 Impending Technologies

#include "Actor/Gameplay/PlayerControllerGameplay.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Actor/Menu/PlayerControllerMenu.h"
#include "Actor/Object/Ball.h"
#include "Actor/Player/PlayerPawn.h"
#include "Kismet/GameplayStatics.h"

APlayerControllerGameplay::APlayerControllerGameplay()
	: InputActionMove(nullptr)
	  , InputActionBoost(nullptr)
	  , bCanMove(false)
{
}

void APlayerControllerGameplay::BeginPlay()
{
	Super::BeginPlay();

	AGameStateGameplay* const GameState = Cast<AGameStateGameplay>(UGameplayStatics::GetGameState(this));
	OnStateChangeHandle = GameState->StateChangeEvent.AddUObject(this, &APlayerControllerGameplay::OnStateChange);

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

void APlayerControllerGameplay::EndPlay(EEndPlayReason::Type const EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	AGameStateGameplay* const GameState = Cast<AGameStateGameplay>(UGameplayStatics::GetGameState(this));
	GameState->StateChangeEvent.Remove(OnStateChangeHandle);
}

void APlayerControllerGameplay::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInput = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInput->BindAction(InputActionMove, ETriggerEvent::Triggered, this, &APlayerControllerGameplay::ActionMove);
	EnhancedInput->BindAction(InputActionBoost, ETriggerEvent::Started, this, &APlayerControllerGameplay::ActionBoost);
}

void APlayerControllerGameplay::ActionMove(FInputActionValue const& InputActionValue)
{
	if(!bCanMove)
	{
		return;
	}
	APlayerPawn const* const PlayerPawn = Cast<APlayerPawn>(GetPawn());
	PlayerPawn->Move(InputActionValue.Get<FVector>());
}

void APlayerControllerGameplay::ActionBoost(FInputActionValue const& InputActionValue)
{
	if(!bCanMove)
	{
		AGameStateGameplay const* GameState = CastChecked<AGameStateGameplay>(UGameplayStatics::GetGameState(this));

		GameState->ProcessInputMain(this);
		return;
	}
	APlayerPawn* const PlayerPawn = Cast<APlayerPawn>(GetPawn());
	PlayerPawn->Boost();
}

void APlayerControllerGameplay::OnStateChange(EGameplayGameState const GameplayGameState)
{
	bCanMove = GameplayGameState == EGameplayGameState::Play;
}
