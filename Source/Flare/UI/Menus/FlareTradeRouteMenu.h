#pragma once

#include "../../Flare.h"

class UFlareTradeRoute;

class SFlareTradeRouteMenu : public SCompoundWidget
{
	/*----------------------------------------------------
		Slate arguments
	----------------------------------------------------*/

	SLATE_BEGIN_ARGS(SFlareTradeRouteMenu){}

	SLATE_ARGUMENT(TWeakObjectPtr<class AFlareMenuManager>, MenuManager)

	SLATE_END_ARGS()


public:

	/*----------------------------------------------------
		Interaction
	----------------------------------------------------*/

	/** Create the widget */
	void Construct(const FArguments& InArgs);

	/** Setup the widget */
	void Setup();

	/** Enter this menu */
	void Enter(UFlareTradeRoute* TradeRoute);

	/** Exit this menu */
	void Exit();

protected:

	/*----------------------------------------------------
		Callbacks
	----------------------------------------------------*/

	/** Go back to the previous menu*/
	void OnBackClicked();


	void OnChangeRouteNameClicked();

    void OnConfirmChangeRouteNameClicked();

    void OnCancelChangeRouteNameClicked();


    /** Are the not editing components visible ? */
    EVisibility GetShowingRouteNameVisibility() const;

    /** Are the not editing components visible ? */
    EVisibility GetEditingRouteNameVisibility() const;


	/** Get route name */
	FText GetTradeRouteName() const;


protected:

	/*----------------------------------------------------
		Protected data
	----------------------------------------------------*/

	// HUD reference
	UPROPERTY()
	TWeakObjectPtr<class AFlareMenuManager>    MenuManager;

	// Menu components
	UFlareTradeRoute*                     TargetTradeRoute;
    bool                                    IsEditingName;

	// Sector data
	TSharedPtr<SComboBox<UFlareSimulatedSector*>> SectorSelector;
    TSharedPtr<SEditableText>                   EditRouteName;

};
