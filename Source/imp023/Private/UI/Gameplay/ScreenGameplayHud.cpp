// Copyright 2024 Impending Technologies

#include "UI/Gameplay/ScreenGameplayHud.h"

#include "Actor/Gameplay/GameStateGameplay.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Data/TeamData.h"
#include "Subsystem/TeamStateSubsystem.h"

void UScreenGameplayHud::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	GameState = GetWorld()->GetGameState<AGameStateGameplay>();

	OnUpdateScoresHandle = GameState->UpdateScoresEvent.AddUObject(this, &UScreenGameplayHud::OnUpdateScores);
	GameState->BroadcastScores();

	BarPeriod1->SetPercent(GameState->Period <= 1 ? 1.0f : 0.0f);
	BarPeriod2->SetPercent(GameState->Period <= 2 ? 1.0f : 0.0f);
	BarPeriod3->SetPercent(GameState->Period <= 3 ? 1.0f : 0.0f);

	UTeamStateSubsystem* const TeamStateSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UTeamStateSubsystem>();
	check(TeamStateSubsystem);

	UTeamData const* const Home = TeamStateSubsystem->GetTeam(ETeam::Home);
	UTeamData const* const Away1 = TeamStateSubsystem->GetTeam(ETeam::Away1);
	UTeamData const* const Away2 = TeamStateSubsystem->GetTeam(ETeam::Away2);

	BarPeriod1->SetFillColorAndOpacity(Home->Color);
	BarPeriod2->SetFillColorAndOpacity(Away1->Color);
	BarPeriod3->SetFillColorAndOpacity(Away2->Color);

	ImageLogoHome->SetBrushFromTexture(Home->Logo.LoadSynchronous());
	ImageLogoAway1->SetBrushFromTexture(Away1->Logo.LoadSynchronous());
	ImageLogoAway2->SetBrushFromTexture(Away2->Logo.LoadSynchronous());

	bDelayTimer = true;
}

void UScreenGameplayHud::NativeDestruct()
{
	Super::NativeDestruct();

	if (GameState)
	{
		GameState->UpdateScoresEvent.Remove(OnUpdateScoresHandle);
	}
}

void UScreenGameplayHud::HandleDelayTimer()
{
	float const Delay = GameState->GetTimerDelayRemaining();
	int const DelayValue = static_cast<int>(Delay);
	float const DelayScale = Delay - DelayValue + 0.1f;

	TextDelay->SetText(FText::AsNumber(DelayValue + 1));
	TextDelay->SetRenderScale(FVector2D::One() * DelayScale);

	bDelayTimer = Delay > 0.0f;
	if (!bDelayTimer)
	{
		TextDelay->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UScreenGameplayHud::HandlePeriodTimer() const
{
	UProgressBar* const Map[4] = {BarPeriod1, BarPeriod2, BarPeriod3};
	check(GameState->Period > 0 && GameState->Period < 4);
	UProgressBar* const BarUpdate = Map[GameState->Period - 1];
	BarUpdate->SetPercent(GameState->GetPeriodTimeRemainingPercent());
}

void UScreenGameplayHud::NativeTick(FGeometry const& MyGeometry, float const InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (bDelayTimer)
	{
		HandleDelayTimer();
	}
	HandlePeriodTimer();
}

void UScreenGameplayHud::OnUpdateScores(TArray<int> const& Scores) const
{
	FNumberFormattingOptions Format = FNumberFormattingOptions();
	Format.SetMinimumIntegralDigits(2);
	TextScoreHome->SetText(FText::AsNumber(Scores[static_cast<int>(ETeam::Home)], &Format));
	TextScoreAway1->SetText(FText::AsNumber(Scores[static_cast<int>(ETeam::Away1)], &Format));
	TextScoreAway2->SetText(FText::AsNumber(Scores[static_cast<int>(ETeam::Away2)], &Format));
}
