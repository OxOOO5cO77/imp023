// Copyright 2024 Impending Technologies

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "GameStateMenu.generated.h"

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

private:
	TObjectPtr<UUserWidget> CurScreen;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Screen Map", meta = (AllowPrivateAccess = "true"))
	TMap<FString,TSubclassOf<UUserWidget>> ScreenMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Screen Map", meta = (AllowPrivateAccess = "true"))
	FString Default;
};
