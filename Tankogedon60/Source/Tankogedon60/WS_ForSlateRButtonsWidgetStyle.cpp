// Fill out your copyright notice in the Description page of Project Settings.


#include "WS_ForSlateRButtonsWidgetStyle.h"

FWS_ForSlateRButtonsStyle::FWS_ForSlateRButtonsStyle()
{
}

FWS_ForSlateRButtonsStyle::~FWS_ForSlateRButtonsStyle()
{
}

const FName FWS_ForSlateRButtonsStyle::TypeName(TEXT("FWS_ForSlateRButtonsStyle"));

const FWS_ForSlateRButtonsStyle& FWS_ForSlateRButtonsStyle::GetDefault()
{
	static FWS_ForSlateRButtonsStyle Default;
	return Default;
}

void FWS_ForSlateRButtonsStyle::GetResources(TArray<const FSlateBrush*>& OutBrushes) const
{
	// Add any brush resources here so that Slate can correctly atlas and reference them
}

