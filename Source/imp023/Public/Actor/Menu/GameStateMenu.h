// Copyright 2024 Impending Technologies

#pragma once

#include "CoreMinimal.h"
#include "Actor/Player/PlayerControllerMenu.h"
#include "GameFramework/GameStateBase.h"
#include "GameStateMenu.generated.h"

class UScreen;
/**
 *
 */
UCLASS()
class IMP023_API AGameStateMenu : public AGameStateBase
{
	GENERATED_BODY()

public:
	AGameStateMenu();

protected:
	virtual void BeginPlay() override;

public:
	void NavigateTo(FString const& Screen);

	void ProcessInputMain(APlayerControllerMenu const* PlayerControllerMenu) const;
	void ProcessInputAlt(APlayerControllerMenu const* PlayerControllerMenu) const;
	void ProcessInputBack(APlayerControllerMenu const* PlayerControllerMenu) const;

private:
	int ControllerIndex(APlayerControllerMenu const* PlayerControllerMenu) const;

private:
	TObjectPtr<UScreen> CurScreen;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Screen Map", meta = (AllowPrivateAccess = "true"))
	TMap<FString, TSubclassOf<UScreen>> ScreenMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Screen Map", meta = (AllowPrivateAccess = "true"))
	FString Default;
};
