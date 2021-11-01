// Fill out your copyright notice in the Description page of Project Settings.


#include "MImageSelectorBoxWidget.h"

#include "Components/Button.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Image.h"
#include "Components/NativeWidgetHost.h"
#include "Components/ScrollBox.h"
#include "Components/VerticalBox.h"

void UMImageSelectorBoxWidget::NativeOnInitialized()
{
	auto widgetSize = static_cast<UCanvasPanelSlot*>(Slot)->GetSize();
	static_cast<UCanvasPanelSlot*>(verticalSelectionBox->Slot)->SetSize( FVector2D( widgetSize.X, widgetSize.Y * ( maxNumberOfEntriesToShow + 1 ) ) );
	
	for( const auto& image : imageSelections )
	{
		int index = selectionOptionsButton.Add( NewObject<UMIndexedButton>( this ) );

		UImage* selectionImage = NewObject<UImage>( this );
		selectionImage->SetBrushFromTexture( image );
		selectionImage->SetBrushSize( widgetSize );

		selectionOptionsButton[index]->AddChild( selectionImage );
		selectionOptionsButton[index]->SetBackgroundColor( FLinearColor( 0, 0, 0, 0 ) );
		selectionOptionsButton[index]->SetBackgroundColor( FLinearColor( 0, 0, 0, 0 ) );
		selectionOptionsButton[index]->SetButtonIndex( index );
		selectionOptionsButton[index]->OnClikedIndexed.BindUFunction( this, "OnImageSelectionOptionClicked" );

		selectionScrollBox->AddChild( selectionOptionsButton[index] );
	}
	selectionScrollBox->SetVisibility( ESlateVisibility::Collapsed );

	UImage* selectionImage = NewObject<UImage>( this );
	selectionImage->SetBrushFromTexture( imageSelections[0] );
	selectionImage->SetBrushSize( widgetSize );
	
	selectionButton->AddChild( selectionImage );
	selectionButton->OnClicked.AddDynamic( this, &UMImageSelectorBoxWidget::ToggleSelectionScrollerVisibility );
}

void UMImageSelectorBoxWidget::SetCurrentSelectionIndex( int index )
{ 
	currentSelectionIndex = index;
	selectionChangedEvent.Broadcast( index );
}

void UMImageSelectorBoxWidget::OpenSelectionBox()
{
	selectionScrollBox->SetVisibility( ESlateVisibility::Visible );
}

void UMImageSelectorBoxWidget::CloseSelectionBox()
{
	selectionScrollBox->SetVisibility( ESlateVisibility::Collapsed );
}

void UMImageSelectorBoxWidget::ToggleSelectionScrollerVisibility()
{
	selectionScrollBox->SetVisibility( selectionScrollBox->GetVisibility() == ESlateVisibility::Visible ? ESlateVisibility::Collapsed : ESlateVisibility::Visible );
}

void UMImageSelectorBoxWidget::OnImageSelectionOptionClicked( int clickedIndex )
{
	SetCurrentSelectionIndex( clickedIndex );
	CloseSelectionBox();
	static_cast<UImage*>( selectionButton->GetChildAt( 0 ) )->SetBrushFromTexture( imageSelections[clickedIndex] );
}
