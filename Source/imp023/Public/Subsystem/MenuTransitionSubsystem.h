// Copyright 2024 Impending Technologies

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MenuTransitionSubsystem.generated.h"

/**
 *
 */
UCLASS()
class IMP023_API UMenuTransitionSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	FString const& GetStartScreen() const;
	void SetStartScreen(FString const& Screen);

private:
	FString StartScreen;
};
