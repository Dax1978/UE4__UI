// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Slate.h"

/**
 * 
 */
class TANKOGEDON60_API FMyCoreStyle
{
public:
	static void Initialize();

	static void Shutdown();

	static const ISlateStyle& Get();

private:
	static TSharedPtr<ISlateStyle> StylePtr;

};
