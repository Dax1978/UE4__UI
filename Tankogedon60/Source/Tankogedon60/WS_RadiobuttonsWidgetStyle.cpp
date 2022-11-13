// Fill out your copyright notice in the Description page of Project Settings.


#include "WS_RadiobuttonsWidgetStyle.h"

FWS_RadiobuttonsStyle::FWS_RadiobuttonsStyle()
{
	// ¬ UE есть встроенна€ библиотека стилей, которые используютс€ в самом UE
	// » основна€ из них (их чуть больше 1-ой: UE UI / Lesson05 / 38:10)
	// » нижеприведенным способом можно получить какой то конкретный стиль:
	CheckBoxStyle = FCoreStyle::Get().GetWidgetStyle<FCheckBoxStyle>("RadioButton");
	TextBlockStyle = FCoreStyle::Get().GetWidgetStyle<FTextBlockStyle>("NormalUnderlinedText");
	// »наче наша структура будет пуста€, будет все черным-черно, и ничего не заработает. Ќам такое не нужно.

	// —ейчас в конструкторе мы задали стили из билиотеки FCoreStyle, чтобы все более менее нормально выгл€дело
}

FWS_RadiobuttonsStyle::~FWS_RadiobuttonsStyle()
{
}

// ѕо большому счету его мен€ть не об€зательно (UE UI / Lesson05 / 29:20)
const FName FWS_RadiobuttonsStyle::TypeName(TEXT("FWS_RadiobuttonsStyle"));

// “от стиль, который будет использоватьс€ по умолчанию
const FWS_RadiobuttonsStyle& FWS_RadiobuttonsStyle::GetDefault()
{
	// ѕри желании мы можем добавить настроек, что бы стиль отличалс€ от поумолчанию (UE UI / Lesson05 / 30:25)
	static FWS_RadiobuttonsStyle Default;
	return Default;
}

// —обирает все ресурсы, дл€ нашего стил€
void FWS_RadiobuttonsStyle::GetResources(TArray<const FSlateBrush*>& OutBrushes) const
{
	// Add any brush resources here so that Slate can correctly atlas and reference them

	// ¬ызовем родительский:
	FSlateWidgetStyle::GetResources(OutBrushes);

	// (UE UI / Lesson05 / 36:10)
	// “ут много вс€кой покапотной магии, но нужно запомнить всего 2 вещи:
	// 
	// 1. ≈сли € использую в своем стиле какие то свои стили
	// (в моем случае это CheckBoxstyle и TextBlockStyle), т.е. все что наследуетс€ от FSlateWidgetStyle
	// то на этих переменных нужно вызвать GetResources:
	CheckBoxStyle.GetResources(OutBrushes);
	TextBlockStyle.GetResources(OutBrushes);

	// 2. ≈сли используем FSlateBrush, то нужно добавить его вручную в этот массив
	//   примеру в header будет:
	// UPROPERTY(EditAnywhere, Category = Appearance)
	// FSlateBrush BackgroundBrush;
	// “.е. создаем как будет выгл€деть наш background, к примеру фонова€ картинка или иное
	// тогда в переданный OutBrushes надо добавить наш BackgroundBrush, вот так:
	// OutBrushes.Add(&BackgroundBrush);
	// 
	// —оответственно, если таких брашей будет более одного, надо каждый из них, таким образом добавить.
	//
	
}

