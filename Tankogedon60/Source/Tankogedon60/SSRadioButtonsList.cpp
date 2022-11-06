// Fill out your copyright notice in the Description page of Project Settings.


#include "SSRadioButtonsList.h"
#include "SlateOptMacros.h"

#include "Widgets/SBoxPanel.h"
#include "Widgets/Input/SCheckBox.h"
#include "Widgets/Text/STextBlock.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SSRadioButtonsList::Construct(const FArguments& InArgs)
{
	OnRadioButtonChanged = InArgs._OnRadioButtonChanged;
	Count = InArgs._Count;

	//ChildSlot
	//[
	//	// Populate the widget
	//	SNew(SVerticalBox)
	//
	//	+ SVerticalBox::Slot()
	//	[
	//		CreateCheckbox(0, "Option 1")
	//	]
	//
	//	+ SVerticalBox::Slot()
	//	[
	//		CreateCheckbox(1, "Option 2")
	//	]
	//
	//	+ SVerticalBox::Slot()
	//	[
	//		CreateCheckbox(2, "Option 3")
	//	]
	//];
			

	ChildSlot
	[
		SAssignNew(Holder, SVerticalBox)	// –аботает практически как SNew, но не просто создает виджет, но и сохран€ет его в переменную
											// “еперь в переменной Holder лежит наш созданный SVerticalBox
	];

	for (int32 i = 0; i < Count.Get(); i++)
	{
		Holder->AddSlot()
		[
			CreateCheckbox(i, TEXT("Option ") + FString::FromInt(i))
		];
	}

	//for (int32 i = 0; i < 3; i++)
	//{
	//	Holder->AddSlot()
	//		[
	//			CreateCheckbox(i, TEXT("Option ") + FString::FromInt(i))
	//		];
	//}
}

//int32 SSRadioButtonsList::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
//{
//	// „то бы слоты не добавл€лись бесконечно, надо добавить проверки
//	if (Holder->GetAllChildren()->Num() == Count.Get())
//	{
//		Holder->ClearChildren();
//		return 0;
//	}
//	
//	for (int32 i = 0; i < Count.Get(); i++)
//	{
//		Holder->AddSlot()
//		[
//			CreateCheckbox(i, TEXT("Option ") + FString::FromInt(i))
//		];
//	}
//
//	return SCompoundWidget::OnPaint(Args, AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);
//}

TSharedRef<SWidget> SSRadioButtonsList::CreateCheckbox(int32 InIndex, FString InText)
{
	return SNew(SCheckBox)
		.IsChecked_Raw(this, &SSRadioButtonsList::IsChecked, InIndex)
		.OnCheckStateChanged_Raw(this, &SSRadioButtonsList::OnCheckboxStateChanged, InIndex)
		[
			SNew(STextBlock)
			.Text(FText::FromString(InText))
		];
}


ECheckBoxState SSRadioButtonsList::IsChecked(int32 InIndex) const
{
	return InIndex == CurrentIndex
		? ECheckBoxState::Checked
		: ECheckBoxState::Unchecked;
}

void SSRadioButtonsList::OnCheckboxStateChanged(ECheckBoxState NewState, int32 InIndex)
{
	if (NewState == ECheckBoxState::Checked)
	{
		CurrentIndex = InIndex;
		OnRadioButtonChanged.ExecuteIfBound(CurrentIndex);
	}
}



END_SLATE_FUNCTION_BUILD_OPTIMIZATION