
#include "../../Flare.h"
#include "FlareTradeRouteMenu.h"

#include "../../Game/FlareGame.h"
#include "../../Player/FlareMenuManager.h"
#include "../../Player/FlarePlayerController.h"

#define LOCTEXT_NAMESPACE "FlareTradeRouteMenu"


/*----------------------------------------------------
	Construct
----------------------------------------------------*/

void SFlareTradeRouteMenu::Construct(const FArguments& InArgs)
{
	// Data
	MenuManager = InArgs._MenuManager;
	const FFlareStyleCatalog& Theme = FFlareStyleSet::GetDefaultTheme();
	AFlarePlayerController* PC = MenuManager->GetPC();

	// Build structure
	ChildSlot
	.HAlign(HAlign_Fill)
	.VAlign(VAlign_Fill)
	[
		SNew(SVerticalBox)

		+ SVerticalBox::Slot()
		.AutoHeight()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Center)
		.Padding(Theme.ContentPadding)
		[
			SNew(SHorizontalBox)

			// Icon
			+ SHorizontalBox::Slot()
			.AutoWidth()
			[
				SNew(SImage).Image(AFlareMenuManager::GetMenuIcon(EFlareMenu::MENU_TradeRoute))
			]

			// Title
			+ SHorizontalBox::Slot()
			.VAlign(VAlign_Center)
			.Padding(Theme.ContentPadding)
			[
				SNew(STextBlock)
				.TextStyle(&Theme.TitleFont)
				.Text(LOCTEXT("TradeRouteInfo", "TRADE ROUTE INFO"))
			]

			// Close
			+ SHorizontalBox::Slot()
			.HAlign(HAlign_Right)
			.VAlign(VAlign_Bottom)
			.Padding(Theme.TitleButtonPadding)
			.AutoWidth()
			[
				SNew(SFlareRoundButton)
				.Text(LOCTEXT("GoOrbit", "Orbital map"))
				.HelpText(LOCTEXT("GoOrbitInfo", "Exit the sector menu and go back to the orbital map"))
				.Icon(AFlareMenuManager::GetMenuIcon(EFlareMenu::MENU_Orbit, true))
				.OnClicked(this, &SFlareTradeRouteMenu::OnBackClicked)
			]
		]

		// Separator
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(FMargin(200, 20))
		[
			SNew(SImage).Image(&Theme.SeparatorBrush)
		]

		// UI container
		+ SVerticalBox::Slot()
		.Padding(Theme.ContentPadding)
		.HAlign(HAlign_Center)
		[
			SNew(SVerticalBox)

			// Header
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(SHorizontalBox)

				// Info
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.HAlign(HAlign_Left)
				.VAlign(VAlign_Top)
				[
					SNew(SVerticalBox)

					// Trade route name
					+ SVerticalBox::Slot()
					.Padding(Theme.TitlePadding)
					.AutoHeight()
					[
						SNew(STextBlock)
						.Text(this, &SFlareTradeRouteMenu::GetTradeRouteName)
						.TextStyle(&Theme.SubTitleFont)
                    ]

                    // Change name
					+ SVerticalBox::Slot()
					.AutoHeight()
					.Padding(Theme.ContentPadding)
					.HAlign(HAlign_Left)
					[
						SNew(SFlareButton)
						.Width(8)
						.Text(LOCTEXT("ChangeName", "Change route name"))
                        .HelpText(LOCTEXT("ChangeNameInfo", "Change the route name"))
						.Icon(FFlareStyleSet::GetIcon("ChangeRouteName"))
						.OnClicked(this, &SFlareTradeRouteMenu::OnChangeRouteNameClicked)
                        .Visibility(this, &SFlareTradeRouteMenu::GetShowingRouteNameVisibility)
					]

                    // Trade route name
                    + SVerticalBox::Slot()
                    .Padding(Theme.TitlePadding)
                    .AutoHeight()
                    [
                        SAssignNew(EditRouteName, SEditableText)
                        .Style(&Theme.TextInputStyle)
                        .Visibility(this, &SFlareTradeRouteMenu::GetEditingRouteNameVisibility)
                    ]

                    // Confirm name
                    + SVerticalBox::Slot()
                    .AutoHeight()
                    .Padding(Theme.ContentPadding)
                    .HAlign(HAlign_Left)
                    [
                        SNew(SFlareButton)
                        .Width(8)
                        .Text(LOCTEXT("ConfirmChangeName", "Confirm"))
                        .HelpText(LOCTEXT("ConfirmChangeNameInfo", "Confirm change the route name"))
                        .Icon(FFlareStyleSet::GetIcon("ConfirmChangeRouteName"))
                        .OnClicked(this, &SFlareTradeRouteMenu::OnConfirmChangeRouteNameClicked)
                        .Visibility(this, &SFlareTradeRouteMenu::GetEditingRouteNameVisibility)
                    ]

                    // Cancel change name
                    + SVerticalBox::Slot()
                    .AutoHeight()
                    .Padding(Theme.ContentPadding)
                    .HAlign(HAlign_Left)
                    [
                        SNew(SFlareButton)
                        .Width(8)
                        .Text(LOCTEXT("CancelChangeName", "Cancel"))
                        .HelpText(LOCTEXT("CancelChangeNameInfo", "Cancel name change"))
                        .Icon(FFlareStyleSet::GetIcon("CancelChangeRouteName"))
                        .OnClicked(this, &SFlareTradeRouteMenu::OnCancelChangeRouteNameClicked)
                        .Visibility(this, &SFlareTradeRouteMenu::GetEditingRouteNameVisibility)
                    ]
				]
			]

			// Content block
			+ SVerticalBox::Slot()
			.VAlign(VAlign_Top)
			[
				SNew(SScrollBox)
				.Style(&Theme.ScrollBoxStyle)
				.ScrollBarStyle(&Theme.ScrollBarStyle)

				+ SScrollBox::Slot()
				[
					SNew(SHorizontalBox)

				]
			]
		]
	];
}


/*----------------------------------------------------
	Interaction
----------------------------------------------------*/

void SFlareTradeRouteMenu::Setup()
{
	SetEnabled(false);
	SetVisibility(EVisibility::Hidden);
}

void SFlareTradeRouteMenu::Enter(UFlareTradeRoute* TradeRoute)
{
	FLOG("SFlareTradeMenu::Enter");

    IsEditingName = false;
	SetEnabled(true);
	SetVisibility(EVisibility::Visible);

	TargetTradeRoute = TradeRoute;
	AFlarePlayerController* PC = MenuManager->GetPC();
}

void SFlareTradeRouteMenu::Exit()
{
	SetEnabled(false);
	TargetTradeRoute = NULL;

	SetVisibility(EVisibility::Hidden);
}

/*----------------------------------------------------
	Callbacks
----------------------------------------------------*/

void SFlareTradeRouteMenu::OnBackClicked()
{
	MenuManager->Back();
}

void SFlareTradeRouteMenu::OnChangeRouteNameClicked()
{
    EditRouteName->SetText(GetTradeRouteName());
    IsEditingName = true;
}

void SFlareTradeRouteMenu::OnCancelChangeRouteNameClicked()
{
    IsEditingName = false;
}

void SFlareTradeRouteMenu::OnConfirmChangeRouteNameClicked()
{
    if (TargetTradeRoute)
    {
        TargetTradeRoute->SetTradeRouteName(EditRouteName->GetText());
    }
    IsEditingName = false;
}

EVisibility SFlareTradeRouteMenu::GetShowingRouteNameVisibility() const
{
    return IsEditingName ? EVisibility::Collapsed : EVisibility::Visible;
}

EVisibility SFlareTradeRouteMenu::GetEditingRouteNameVisibility() const
{
    return IsEditingName ? EVisibility::Visible : EVisibility::Collapsed;
}

/** Get a button text */
FText SFlareTradeRouteMenu::GetTradeRouteName() const
{
	FText Result;

	if (TargetTradeRoute)
	{
		Result = TargetTradeRoute->GetTradeRouteName();
	}

	return Result;
}

#undef LOCTEXT_NAMESPACE

