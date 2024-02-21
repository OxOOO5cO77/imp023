// Copyright 2024 Impending Technologies

#include "UI/Menu/ScreenPlayerSelect.h"

#include "Actor/Menu/GameStateMenu.h"
#include "Component/CompTeam.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Subsystem/TeamStateSubsystem.h"

static constexpr int GMaxSlot = 2;
static constexpr ETeam SlotToTeam[] = {ETeam::Home, ETeam::Away1, ETeam::Away2};

void UScreenPlayerSelect::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	TextAway1->SetVisibility(ESlateVisibility::Hidden);
	TextAway2->SetVisibility(ESlateVisibility::Hidden);

	TrackedSlotIndex = 0;

	UTeamStateSubsystem* const TeamStateSubsystem = UGameplayStatics::GetGameInstance(this)->GetSubsystem<UTeamStateSubsystem>();
	check(TeamStateSubsystem);
	TeamStateSubsystem->InitializeTeams();

	for (ETeam const Team : SlotToTeam)
	{
		SetupTeam(Team);
	}
}

void UScreenPlayerSelect::SetupTeam(ETeam const Team)
{
	UImage* Image = nullptr;

	switch (Team)
	{
		case ETeam::None:
			checkNoEntry();
			break;
		case ETeam::Home:
			Image = ImageHome;
			break;
		case ETeam::Away1:
			Image = ImageAway1;
			break;
		case ETeam::Away2:
			Image = ImageAway2;
			break;
	}

	UTeamStateSubsystem const* const TeamStateSubsystem = UGameplayStatics::GetGameInstance(this)->GetSubsystem<UTeamStateSubsystem>();
	check(TeamStateSubsystem);

	UTexture2D* Asset = TeamStateSubsystem->GetLogo(this, Team);
	Image->SetBrushFromTexture(Asset);
}

void UScreenPlayerSelect::OnInputMain(int const PlayerIndex)
{
	Super::OnInputMain(PlayerIndex);

	if (TrackedSlotIndex > GMaxSlot)
	{
		GetWorld()->ServerTravel("/Game/Level/Arena");
		return;
	}

	AGameStateMenu* const GameState = CastChecked<AGameStateMenu>(UGameplayStatics::GetGameState(this));

	bool const Success = GameState->SetPlayerToTeam(PlayerIndex, SlotToTeam[TrackedSlotIndex]);

	if (Success)
	{
		Advance(PlayerIndex, true);
	}
}

void UScreenPlayerSelect::OnInputAlt(int const PlayerIndex)
{
	Super::OnInputMain(PlayerIndex);

	if (TrackedSlotIndex > GMaxSlot)
	{
		return;
	}

	Advance(PlayerIndex, false);
}

void UScreenPlayerSelect::Advance(int const PlayerIndex, bool const IsHuman)
{
	TWeakObjectPtr<UTextBlock> const CurText = TextFromSlot(TrackedSlotIndex);
	CurText->SetText(IsHuman ? FText::Format(INVTEXT("PLAYER {0}"), PlayerIndex) : INVTEXT("CPU"));

	++TrackedSlotIndex;

	if (TrackedSlotIndex <= GMaxSlot)
	{
		TWeakObjectPtr<UTextBlock> const NextText = TextFromSlot(TrackedSlotIndex);
		NextText->SetVisibility(ESlateVisibility::Visible);
	}
}

void UScreenPlayerSelect::OnInputBack(int const PlayerIndex)
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

	AGameStateMenu* const GameState = Cast<AGameStateMenu>(UGameplayStatics::GetGameState(this));
	check(GameState);

	GameState->DisassociateTeam(SlotToTeam[TrackedSlotIndex]);

	TWeakObjectPtr<UTextBlock> const PrevText = TextFromSlot(TrackedSlotIndex);
	PrevText->SetVisibility(ESlateVisibility::Visible);
	PrevText->SetText(INVTEXT("CHOOSE"));
}

TWeakObjectPtr<UTextBlock> UScreenPlayerSelect::TextFromSlot(uint const SlotIndex) const
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
