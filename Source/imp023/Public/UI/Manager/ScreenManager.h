// Copyright 2024 Impending Technologies

#pragma once

#include "CoreMinimal.h"
#include "Screen.h"
#include "UObject/Object.h"
#include "ScreenManager.generated.h"

/**
 *
 */
UCLASS(Blueprintable, BlueprintType)
class IMP023_API UScreenManager : public UObject
{
	GENERATED_BODY()
public:
	UScreenManager();
public:
	void Start();
	void NavigateTo(FString const& Screen);

public:
	void HandleInputMain(int ControllerIndex) const;
	void HandleInputAlt(int ControllerIndex) const;
	void HandleInputBack(int ControllerIndex) const;
	void HandleInputMove(int ControllerIndex, FVector2D const& Direction) const;

private:
	UPROPERTY()
	TObjectPtr<UScreen> CurScreen;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Screen Map", meta = (AllowPrivateAccess = "true"))
	TMap<FString, TSubclassOf<UScreen>> ScreenMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Screen Map", meta = (AllowPrivateAccess = "true"))
	FString Default;
};
