// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "WS_RadiobuttonsWidgetStyle.h"

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/SViewport.h"


DECLARE_DELEGATE_OneParam(FOnRadioButtonChanged, int32 /*NewRadioChoise*/);

/**
 * 
 */
class TANKOGEDON60_API SSRadioButtonsList : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSRadioButtonsList)
	{}

	SLATE_ATTRIBUTE(int32, Count);

	/** Called when radio choice is changed */
	SLATE_EVENT(FOnRadioButtonChanged, OnRadioButtonChanged);

	// Что бы наш стиль из WS_RadiobuttonsWidgetStyle заработал
	SLATE_STYLE_ARGUMENT(FWS_RadiobuttonsStyle, Style);

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	FOnRadioButtonChanged OnRadioButtonChanged;

	// У слэйта есть метод "почти" tick:
	//virtual int32 OnPaint
	//(
	//	const FPaintArgs& Args,
	//	const FGeometry& AllottedGeometry,
	//	const FSlateRect& MyCullingRect,
	//	FSlateWindowElementList& OutDrawElements,
	//	int32 LayerId,
	//	const FWidgetStyle& InWidgetStyle,
	//	bool bParentEnabled
	//) const;

private:
	TAttribute<int32> Count;

	TSharedRef<SWidget> CreateCheckbox(int32 InIndex, FString InText);
	TSharedPtr<SVerticalBox> Holder;	// Переменная для сохранения созданного виджета SVerticalBox

	// ERadioChoice CurrentChoice;
	int32 CurrentIndex = 0;
	

	ECheckBoxState IsChecked(int32 InIndex) const;

	void OnCheckboxStateChanged(ECheckBoxState NewState, int32 InIndex);

	const FCheckBoxStyle* CheckBoxStyle = nullptr;
	const FTextBlockStyle* TextBlockStyle = nullptr;

	// Как альтернатива, когда просто передаем весь стиль
	// const FWS_RadiobuttonsStyle* Style = nullptr;
		
};
