// Copyright 2024 Impending Technologies


#include "UI/Manager/ScreenManager.h"

#include "Subsystem/MenuTransitionSubsystem.h"

UScreenManager::UScreenManager()
	: CurScreen(nullptr)
{
}

void UScreenManager::Start()
{
	UMenuTransitionSubsystem* const MenuTransitionSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UMenuTransitionSubsystem>();

	FString const& StartScreen = MenuTransitionSubsystem->GetStartScreen();
	FString StartScreenToUse = StartScreen.IsEmpty() ? Default : StartScreen;
	check(!StartScreenToUse.IsEmpty());
	NavigateTo(StartScreenToUse);

	MenuTransitionSubsystem->SetStartScreen(Default);
}

void UScreenManager::NavigateTo(FString const& Screen)
{
	check(ScreenMap.Contains(Screen));

	if (CurScreen != nullptr)
	{
		CurScreen->RemoveFromParent();
		CurScreen = nullptr;
	}

	TSubclassOf<UUserWidget> const Destination = ScreenMap[Screen];
	check(Destination);

	CurScreen = CreateWidget<UScreen>(GetWorld(), Destination);
	check(CurScreen);

	CurScreen->Attach(this);
	CurScreen->AddToViewport();
}

void UScreenManager::HandleInputMain(int const ControllerIndex) const
{
	CurScreen->OnInputMain(ControllerIndex);
}

void UScreenManager::HandleInputAlt(int const ControllerIndex) const
{
	CurScreen->OnInputAlt(ControllerIndex);
}

void UScreenManager::HandleInputBack(int const ControllerIndex) const
{
	CurScreen->OnInputBack(ControllerIndex);
}

void UScreenManager::HandleInputMove(int const ControllerIndex, FVector2D const& Direction) const
{
	FVector2D const AbsDirection = Direction.GetAbs();

	if (AbsDirection.IsNearlyZero())
	{
		return;
	}

	if (AbsDirection.X > AbsDirection.Y)
	{
		if (Direction.X > 0)
		{
			CurScreen->OnInputRight(ControllerIndex);
		}
		else
		{
			CurScreen->OnInputLeft(ControllerIndex);
		}
	}
	else
	{
		if (Direction.Y > 0)
		{
			CurScreen->OnInputUp(ControllerIndex);
		}
		else
		{
			CurScreen->OnInputDown(ControllerIndex);
		}
	}
}
