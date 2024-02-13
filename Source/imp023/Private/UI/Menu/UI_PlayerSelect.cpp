// Copyright 2024 Impending Technologies


#include "UI/Menu/UI_PlayerSelect.h"

#include "Components/TextBlock.h"

void UUI_PlayerSelect::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	TextAway1->SetVisibility(ESlateVisibility::Hidden);
	TextAway2->SetVisibility(ESlateVisibility::Hidden);
}
