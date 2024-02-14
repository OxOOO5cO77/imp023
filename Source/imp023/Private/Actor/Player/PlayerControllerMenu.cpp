// Copyright 2024 Impending Technologies


#include "Actor/Player/PlayerControllerMenu.h"

#include "Actor/Menu/GameStateMenu.h"
#include "Kismet/GameplayStatics.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"


//static ConstructorHelpers::FObjectFinder<UStaticMesh> GroundShape(TEXT("StaticMesh'/Game/Shapes/Ground/ground_shape_1.ground_shape_1'"));

void APlayerControllerMenu::BeginPlay()
{
	Super::BeginPlay();

	GameState = Cast<AGameStateMenu>(UGameplayStatics::GetGameState(this));

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
}

void APlayerControllerMenu::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInput = CastChecked<UEnhancedInputComponent>(InputComponent);
	check(EnhancedInput);

	EnhancedInput->BindAction(InputActionMain, ETriggerEvent::Started, this, &APlayerControllerMenu::ActionMain);
	EnhancedInput->BindAction(InputActionAlt, ETriggerEvent::Started, this, &APlayerControllerMenu::ActionAlt);
	EnhancedInput->BindAction(InputActionBack, ETriggerEvent::Started, this, &APlayerControllerMenu::ActionBack);
}

void APlayerControllerMenu::ActionMain(const FInputActionValue& InputActionValue)
{
	GameState->ProcessInputMain(this);
}
void APlayerControllerMenu::ActionAlt(const FInputActionValue& InputActionValue)
{
	GameState->ProcessInputAlt(this);
}
void APlayerControllerMenu::ActionBack(const FInputActionValue& InputActionValue)
{
	GameState->ProcessInputBack(this);
}
