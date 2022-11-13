// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateWidgetStyle.h"
#include "Styling/SlateWidgetStyleContainerBase.h"

#include "WS_ForSlateRButtonsWidgetStyle.generated.h"

/**
 * 
 */
USTRUCT()
struct TANKOGEDON60_API FWS_ForSlateRButtonsStyle : public FSlateWidgetStyle
{
	GENERATED_USTRUCT_BODY()

	FWS_ForSlateRButtonsStyle();
	virtual ~FWS_ForSlateRButtonsStyle();

	// FSlateWidgetStyle
	virtual void GetResources(TArray<const FSlateBrush*>& OutBrushes) const override;
	static const FName TypeName;
	virtual const FName GetTypeName() const override { return TypeName; };
	static const FWS_ForSlateRButtonsStyle& GetDefault();
};

/**
 */
UCLASS(hidecategories=Object, MinimalAPI)
class UWS_ForSlateRButtonsWidgetStyle : public USlateWidgetStyleContainerBase
{
	GENERATED_BODY()

public:
	/** The actual data describing the widget appearance. */
	UPROPERTY(Category=Appearance, EditAnywhere, meta=(ShowOnlyInnerProperties))
	FWS_ForSlateRButtonsStyle WidgetStyle;

	virtual const struct FSlateWidgetStyle* const GetStyle() const override
	{
		return static_cast< const struct FSlateWidgetStyle* >( &WidgetStyle );
	}
};
