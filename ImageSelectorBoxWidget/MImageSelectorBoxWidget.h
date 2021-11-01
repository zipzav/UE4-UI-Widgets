// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MBaseUserWidget.h"
#include "MIndexedButton.h"
#include "MImageSelectorBoxWidget.generated.h"

DECLARE_EVENT_OneParam( UMImageSelectorBoxWidget, SelectionChangedEvent, int )
UCLASS()
class NODEMAGIKA_API UMImageSelectorBoxWidget : public UMBaseUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
	int GetCurrentSelectionIndex() const { return currentSelectionIndex; }

	UFUNCTION()
	void SetCurrentSelectionIndex( int index );

	UFUNCTION()
	void OpenSelectionBox();
	
	UFUNCTION()
	void CloseSelectionBox();

	UFUNCTION()
	void ToggleSelectionScrollerVisibility();

	void NativeOnInitialized() override;

protected:
	UPROPERTY( EditAnywhere, Category = "Selector Inputs" )
	TArray<UTexture2D*> imageSelections;

	UFUNCTION()
	void OnImageSelectionOptionClicked( int clickedIndex );

private:
	UPROPERTY( meta = (BindWidget) )
	class UVerticalBox* verticalSelectionBox;

	UPROPERTY( meta = (BindWidget) )
	class UButton* selectionButton;

	UPROPERTY( meta = (BindWidget) )
	class UScrollBox* selectionScrollBox;

	UPROPERTY( EditAnywhere, Category = "Selector Inputs" )
	uint32 maxNumberOfEntriesToShow = 3;

	SelectionChangedEvent selectionChangedEvent;

	TArray<UMIndexedButton*> selectionOptionsButton;
	int currentSelectionIndex = 0;
};
