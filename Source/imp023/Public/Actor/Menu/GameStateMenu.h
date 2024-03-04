// Copyright 2024 Impending Technologies

#pragma once

#include "CoreMinimal.h"
#include "Actor/Menu/PlayerControllerMenu.h"
#include "Enum/ETeam.h"
#include "GameFramework/GameStateBase.h"
#include "UI/Manager/ScreenManager.h"
#include "GameStateMenu.generated.h"

class UScreen;
/**
 *
 */
UCLASS()
class IMP023_API AGameStateMenu : public AGameStateBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	void ProcessInputMain(APlayerControllerMenu const* PlayerControllerMenu) const;
	void ProcessInputAlt(APlayerControllerMenu const* PlayerControllerMenu) const;
	void ProcessInputBack(APlayerControllerMenu const* PlayerControllerMenu) const;
	void ProcessInputMove(APlayerControllerMenu const* PlayerControllerMenu, FVector2D const& Direction) const;

	void SetExpectedHumans(uint const Humans);
	uint GetExpectedHumans() const;
	bool SetPlayerToTeam(int const PlayerIndex, ETeam const Team);
	void DisassociateTeam(ETeam const Team);

private:
	int ControllerIndex(APlayerControllerMenu const* const PlayerControllerMenu) const;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ScreenManager", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UScreenManager> BPScreenManager;

	UPROPERTY()
	UScreenManager* ScreenManager;

	uint ExpectedHumans;
};
