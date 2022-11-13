// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_ForSlateRadiobuttons.h"
#include "SSRadioButtonsList.h"

void UWidget_ForSlateRadiobuttons::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);

	RadioButtons.Reset();
}

TSharedRef<SWidget> UWidget_ForSlateRadiobuttons::RebuildWidget()
{
	RadioButtons = SNew(SSRadioButtonsList)
		.Count_UObject(this, &ThisClass::GetCount)
		.OnRadioButtonChanged_UObject(this, &ThisClass::OnRadioButtonChangedFunc)
		// Здесь добавляем наш стиль
		// Но наш слейтовский стиль и виджет, должен жить столько же, сколько UMG виджет
		// соответственно в ReleaseSlateResources(bool bReleaseChildren) обязательно должно быть прописано: RadioButtons.Reset();
		// иначе могут быть неприятности, типа UMG виджет перестал существовать, а слейтовский все еще продолжает...
		// поэтому мы и должны почистить память указывая RadioButtons.Reset();
		.Style(&WidgetStyle); // ; - ТОЛЬКО на строке с последней точкой!!!

	return RadioButtons.ToSharedRef();
}

int32 UWidget_ForSlateRadiobuttons::GetCount() const
{
	return Count;
}

void UWidget_ForSlateRadiobuttons::OnRadioButtonChangedFunc(int32 NewSelectedButton)
{
	OnRadioButtonChanged.Broadcast(NewSelectedButton);
}
