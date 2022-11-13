// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCoreStyle.h"
#include <Runtime/Engine/Public/Slate/SlateGameResources.h>

#define IMAGE_BRUSH( RelativePath, ... ) FSlateImageBrush(Style->RootToContentDir(RelativePath, TEXT(".png")), __VA_ARGS__)

TSharedPtr<ISlateStyle> FMyCoreStyle::StylePtr;

TSharedPtr<ISlateStyle> CreateStyle()
{
	// const FString ScopeToDirectory("Game/UI");
	// TSharedPtr<ISlateStyle> Style = FSlateGameResources::New(FName("MyCoreStyle"), ScopeToDirectory, ScopeToDirectory);

	FString Path = FPaths::ProjectConfigDir() / TEXT("/UI");
	// FString Path = "Game/Widgets";
	TSharedPtr<FSlateStyleSet> Style = FSlateGameResources::New(FName("MyCoreStyle"), Path, Path);

	Style->Set("Red", FLinearColor::Red);
	Style->Set("DefaultPadding", FMargin(5.f));
	Style->Set("Cat", new IMAGE_BRUSH("cat", FVector2D(256.f)));

	return Style;
}

#undef IMAGE_BRUSH

void FMyCoreStyle::Initialize()
{
	Shutdown();

	StylePtr = CreateStyle();
	FSlateStyleRegistry::RegisterSlateStyle(*StylePtr);
}

void FMyCoreStyle::Shutdown()
{
	if (StylePtr.IsValid())
	{
		FSlateStyleRegistry::UnRegisterSlateStyle(*StylePtr);
		StylePtr.Reset();
	}
}

const ISlateStyle& FMyCoreStyle::Get()
{
	// TODO: вставьте здесь оператор return
	if (StylePtr.IsValid())
	{
		Initialize();
	}
	return *StylePtr;
}
