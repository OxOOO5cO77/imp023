// Copyright 2024 Impending Technologies

#pragma once

#include "CoreMinimal.h"
#include "GameStateGameplay.h"
#include "InputMappingContext.h"
#include "GameFramework/PlayerController.h"
#include "PlayerControllerGameplay.generated.h"

class UInputAction;
/**
 *
 */
UCLASS()
class IMP023_API APlayerControllerGameplay : public APlayerController
{
	GENERATED_BODY()

public:
	APlayerControllerGameplay();
public:
	virtual void BeginPlay() override;
	virtual void EndPlay(EEndPlayReason::Type const EndPlayReason) override;
	virtual void SetupInputComponent() override;
private:
	void ActionMove(FInputActionValue const& InputActionValue);
	void ActionBoost(FInputActionValue const& InputActionValue);
	void OnStateChange(EGameplayGameState const GameplayGameState);

private:
	UPROPERTY(EditAnywhere, Category="Input", meta = (AllowPrivateAccess = "true"))
	TSoftObjectPtr<UInputMappingContext> InputMapping;
	UPROPERTY(EditAnywhere, Category="Input", meta = (AllowPrivateAccess = "true"))
	UInputAction const* InputActionMove;
	UPROPERTY(EditAnywhere, Category="Input", meta = (AllowPrivateAccess = "true"))
	UInputAction const* InputActionBoost;

private:
	FDelegateHandle OnStateChangeHandle;
	bool bCanMove;
};
