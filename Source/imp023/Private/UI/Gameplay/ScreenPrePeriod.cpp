// Copyright 2024 Impending Technologies


#include "UI/Gameplay/ScreenPrePeriod.h"

#include "Actor/Gameplay/GameStateGameplay.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Subsystem/TeamStateSubsystem.h"

void UScreenPrePeriod::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	AGameStateGameplay const* GameState = CastChecked<AGameStateGameplay>(UGameplayStatics::GetGameState(GetWorld()));

	TextPeriod->SetText(FText::Format(INVTEXT("Period {0}"), GameState->Period));

	UTeamStateSubsystem* const TeamStateSubsystem = UGameplayStatics::GetGameInstance(this)->GetSubsystem<UTeamStateSubsystem>();
	check(TeamStateSubsystem);

	ImageHome->SetBrushFromTexture(TeamStateSubsystem->GetLogo(this, ETeam::Home));
	ImageAway1->SetBrushFromTexture(TeamStateSubsystem->GetLogo(this, ETeam::Away1));
	ImageAway2->SetBrushFromTexture(TeamStateSubsystem->GetLogo(this, ETeam::Away2));
}

void UScreenPrePeriod::OnInputMain(int const PlayerIndex)
{
	Super::OnInputMain(PlayerIndex);

	AGameStateGameplay* GameState = CastChecked<AGameStateGameplay>(UGameplayStatics::GetGameState(GetWorld()));

	GameState->SetState(EGameplayGameState::PrePlay);
}
