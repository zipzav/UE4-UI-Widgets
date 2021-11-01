// Fill out your copyright notice in the Description page of Project Settings.


#include "MIndexedButton.h"

#include "Components/ButtonSlot.h"

TSharedRef<SWidget> UMIndexedButton::RebuildWidget()
{
	MyButton = SNew( SButton )
		.OnClicked( BIND_UOBJECT_DELEGATE( FOnClicked, IndexedButtonHandledClick ) )
		.OnPressed( BIND_UOBJECT_DELEGATE( FSimpleDelegate, SlateHandlePressed ) )
		.OnReleased( BIND_UOBJECT_DELEGATE( FSimpleDelegate, SlateHandleReleased ) )
		.OnHovered_UObject( this, &ThisClass::SlateHandleHovered )
		.OnUnhovered_UObject( this, &ThisClass::SlateHandleUnhovered )
		.ButtonStyle( &WidgetStyle )
		.ClickMethod( ClickMethod )
		.TouchMethod( TouchMethod )
		.PressMethod( PressMethod )
		.IsFocusable( IsFocusable )
		;

	if( GetChildrenCount() > 0 )
	{
		Cast<UButtonSlot>( GetContentSlot() )->BuildSlot( MyButton.ToSharedRef() );
	}

	return MyButton.ToSharedRef();
}

FReply UMIndexedButton::IndexedButtonHandledClick()
{
	OnClikedIndexed.ExecuteIfBound( buttonIndex );
	return FReply::Handled();
}
