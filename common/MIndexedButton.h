// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "Input/Reply.h"
#include "MIndexedButton.generated.h"

/**
 * 
 */
DECLARE_DELEGATE_OneParam( FOnImageSelectionClicked, int )

UCLASS()
class NODEMAGIKA_API UMIndexedButton : public UButton
{
	GENERATED_BODY()
public:
	FOnImageSelectionClicked OnClikedIndexed;

	virtual TSharedRef<SWidget> RebuildWidget();

	UFUNCTION()
	int GetButtonIndex() const { return buttonIndex; }

	UFUNCTION()
	void SetButtonIndex( int index ) { buttonIndex = index; }

private:
	FReply IndexedButtonHandledClick();
	int buttonIndex;
};
