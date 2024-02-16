// Copyright 2024 Impending Technologies

#pragma once

#include "CoreMinimal.h"
#include "Actor/Menu/PlayerControllerMenu.h"
#include "Component/CompTeam.h"
#include "GameFramework/GameStateBase.h"
#include "UI/Menu/UI_PlayerSelect.h"
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

	bool SetPlayerToTeam(int const PlayerIndex, ETeam const Team);
	void DisassociateTeam(ETeam const Team);

private:
	int ControllerIndex(APlayerControllerMenu const* const PlayerControllerMenu) const;

private:
	UPROPERTY()
	TObjectPtr<UScreen> CurScreen;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Screen Map", meta = (AllowPrivateAccess = "true"))
	TMap<FString, TSubclassOf<UScreen>> ScreenMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Screen Map", meta = (AllowPrivateAccess = "true"))
	FString Default;
};
