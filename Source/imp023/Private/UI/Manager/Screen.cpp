// Copyright 2024 Impending Technologies

#include "UI/Manager/Screen.h"

void UScreen::Attach(UScreenManager* const Manager)
{
	ScreenManager = Manager;
}

void UScreen::HandleInputMain(int const Idx)
{
	OnInputMain(Idx);
}

void UScreen::HandleInputAlt(int const Idx)
{
	OnInputAlt(Idx);
}

void UScreen::HandleInputBack(int const Idx)
{
	OnInputBack(Idx);
}

void UScreen::OnInputMain(int const Idx)
{
}

void UScreen::OnInputAlt(int const Idx)
{
}

void UScreen::OnInputBack(int const Idx)
{
}
