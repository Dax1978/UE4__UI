// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateWidgetStyle.h"
#include "Styling/SlateWidgetStyleContainerBase.h"

#include "WS_RadiobuttonsWidgetStyle.generated.h"

/**
 * 
 */
USTRUCT()
struct TANKOGEDON60_API FWS_RadiobuttonsStyle : public FSlateWidgetStyle
{
	GENERATED_USTRUCT_BODY()

	FWS_RadiobuttonsStyle();
	virtual ~FWS_RadiobuttonsStyle();

	UPROPERTY(EditAnywhere, Category = Appearance)
	FCheckBoxStyle CheckBoxStyle;

	UPROPERTY(EditAnywhere, Category = Appearance)
	FTextBlockStyle TextBlockStyle;

	// FSlateWidgetStyle
	virtual void GetResources(TArray<const FSlateBrush*>& OutBrushes) const override;
	static const FName TypeName;
	virtual const FName GetTypeName() const override { return TypeName; };
	static const FWS_RadiobuttonsStyle& GetDefault();
};

/**
 */
UCLASS(hidecategories=Object, MinimalAPI)
class UWS_RadiobuttonsWidgetStyle : public USlateWidgetStyleContainerBase
{
	GENERATED_BODY()

public:
	/** The actual data describing the widget appearance. */
	UPROPERTY(Category=Appearance, EditAnywhere, meta=(ShowOnlyInnerProperties))
	FWS_RadiobuttonsStyle WidgetStyle;

	virtual const struct FSlateWidgetStyle* const GetStyle() const override
	{
		return static_cast< const struct FSlateWidgetStyle* >( &WidgetStyle );
	}
};
