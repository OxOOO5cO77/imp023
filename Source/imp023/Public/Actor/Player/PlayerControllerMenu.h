// Copyright 2024 Impending Technologies

#pragma once

#include "CoreMinimal.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "GameFramework/PlayerController.h"
#include "PlayerControllerMenu.generated.h"

class UInputAction;
class AGameStateMenu;
/**
 *
 */
UCLASS()
class IMP023_API APlayerControllerMenu : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	void ActionMain(const FInputActionValue& InputActionValue);
	void ActionAlt(const FInputActionValue& InputActionValue);
	void ActionBack(const FInputActionValue& InputActionValue);

private:
	UPROPERTY(EditAnywhere, Category="Input")
	TSoftObjectPtr<UInputMappingContext> InputMapping;
	UPROPERTY(EditAnywhere, Category="Input", meta = (AllowPrivateAccess = "true"))
	UInputAction const* InputActionMain;
	UPROPERTY(EditAnywhere, Category="Input", meta = (AllowPrivateAccess = "true"))
	UInputAction const* InputActionAlt;
	UPROPERTY(EditAnywhere, Category="Input", meta = (AllowPrivateAccess = "true"))
	UInputAction const* InputActionBack;

private:
	UPROPERTY()
	AGameStateMenu* GameState;
};
