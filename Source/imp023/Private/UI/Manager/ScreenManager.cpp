// Copyright 2024 Impending Technologies


#include "UI/Manager/ScreenManager.h"

UScreenManager::UScreenManager()
	: CurScreen(nullptr)
{
}

void UScreenManager::Start()
{
	check(!Default.IsEmpty());
	NavigateTo(Default);
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

void UScreenManager::HandleInputMain(int const Idx) const
{
	CurScreen->HandleInputMain(Idx);
}

void UScreenManager::HandleInputAlt(int const Idx) const
{
	CurScreen->HandleInputAlt(Idx);
}

void UScreenManager::HandleInputBack(int const Idx) const
{
	CurScreen->HandleInputBack(Idx);
}
