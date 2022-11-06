// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Widget.h"
#include "Widget_ForSlateRadiobuttons.generated.h"

/**
 * 
 */

class SSRadioButtonsList;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRadioButtonChangedEvent, int32, NewSelectedButton);

UCLASS()
class TANKOGEDON60_API UWidget_ForSlateRadiobuttons : public UWidget
{
	GENERATED_BODY()
	
public:

#if WITH_EDITOR
	virtual const FText GetPaletteCategory() override { return FText::FromString(TEXT("Input")); };
#endif

	UPROPERTY(EditAnywhere)
	int32 Count;

	UPROPERTY(BlueprintAssignable)
	FOnRadioButtonChangedEvent OnRadioButtonChanged;

	virtual void ReleaseSlateResources(bool bReleaseChildren) override;

protected:
	virtual TSharedRef<SWidget> RebuildWidget() override;

private:
	int32 GetCount() const;

	TSharedPtr<SSRadioButtonsList> RadioButtons;

	void OnRadioButtonChangedFunc(int32 NewSelectedButton);
};
