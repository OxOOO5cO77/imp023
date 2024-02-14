// Copyright 2024 Impending Technologies

#include "UI/Menu/UI_PlayerSelect.h"

#include "Components/TextBlock.h"

static int constexpr GMaxSlot = 2;

void UUI_PlayerSelect::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	TextAway1->SetVisibility(ESlateVisibility::Hidden);
	TextAway2->SetVisibility(ESlateVisibility::Hidden);

	TrackedSlotIndex = 0;
}

void UUI_PlayerSelect::OnInputMain(int const PlayerIndex)
{
	Super::OnInputMain(PlayerIndex);

	if (TrackedSlotIndex > GMaxSlot)
	{
		return;
	}

	Advance(PlayerIndex, true);
}

void UUI_PlayerSelect::OnInputAlt(int const PlayerIndex)
{
	Super::OnInputMain(PlayerIndex);

	Advance(PlayerIndex, false);
}

void UUI_PlayerSelect::Advance(int const PlayerIndex, bool const IsHuman)
{
	if (TrackedSlotIndex > GMaxSlot)
	{
		return;
	}

	TWeakObjectPtr<UTextBlock> const CurText = TextFromSlot(TrackedSlotIndex);
	CurText->SetText(IsHuman ? FText::Format(INVTEXT("PLAYER {0}"), PlayerIndex) : INVTEXT("CPU"));

	++TrackedSlotIndex;

	if (TrackedSlotIndex <= GMaxSlot)
	{
		TWeakObjectPtr<UTextBlock> const NextText = TextFromSlot(TrackedSlotIndex);
		NextText->SetVisibility(ESlateVisibility::Visible);
	}
}

void UUI_PlayerSelect::OnInputBack(int const PlayerIndex)
{
	if (TrackedSlotIndex == 0)
	{
		return;
	}

	if (TrackedSlotIndex <= GMaxSlot)
	{
		TWeakObjectPtr<UTextBlock> const CurText = TextFromSlot(TrackedSlotIndex);
		CurText->SetVisibility(ESlateVisibility::Hidden);
	}

	--TrackedSlotIndex;

	TWeakObjectPtr<UTextBlock> const PrevText = TextFromSlot(TrackedSlotIndex);
	PrevText->SetVisibility(ESlateVisibility::Visible);
	PrevText->SetText(INVTEXT("CHOOSE"));
}

TWeakObjectPtr<UTextBlock> UUI_PlayerSelect::TextFromSlot(uint const SlotIndex) const
{
	switch (SlotIndex)
	{
		case 0:
			return TextHome;
		case 1:
			return TextAway1;
		case 2:
			return TextAway2;
		default:
			checkNoEntry();
	}
	return nullptr;
}
