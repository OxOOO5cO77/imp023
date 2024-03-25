// Copyright 2024 Impending Technologies


#include "UI/Menu/PartStanding.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Data/TeamData.h"
#include "Subsystem/LeagueSubsystem.h"

void UPartStanding::Setup(FLeagueTeam const* const LeagueTeam, FText const& RankText) const
{
	ImageTeam->SetBrushFromTexture(LeagueTeam->Team->Logo.LoadSynchronous());
	TextRank->SetText(RankText);
	TextGP->SetText(FText::AsNumber(LeagueTeam->Games));
	TextW->SetText(FText::AsNumber(LeagueTeam->Wins));
	TextSW->SetText(FText::AsNumber(LeagueTeam->SharedWins));
	TextD->SetText(FText::AsNumber(LeagueTeam->Draws));
	TextSL->SetText(FText::AsNumber(LeagueTeam->SharedLosses));
	TextL->SetText(FText::AsNumber(LeagueTeam->Losses));
	TextPts->SetText(FText::AsNumber(LeagueTeam->Points()));
}
