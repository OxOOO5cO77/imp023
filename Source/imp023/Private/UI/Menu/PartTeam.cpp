// Copyright 2024 Impending Technologies


#include "UI/Menu/PartTeam.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Data/TeamData.h"

void UPartTeam::SetLogo(UTeamData const* const TeamData) const
{
	ImageTeam->SetBrushFromTexture(TeamData->Logo.LoadSynchronous());
}

void UPartTeam::SetSelectedColor(FLinearColor const& Color) const
{
	ImageSelectTeam->SetBrushTintColor(Color);
}

void UPartTeam::SetText(FString const& Text) const
{
	TextTeam->SetVisibility(Text.IsEmpty() ? ESlateVisibility::Hidden : ESlateVisibility::Visible);
	TextTeam->SetText(FText::FromString(Text));
}
