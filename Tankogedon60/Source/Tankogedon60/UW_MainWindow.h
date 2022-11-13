// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/NativeWidgetHost.h"
#include "UW_MainWindow.generated.h"

/**
 * 
 */

class UButton;
class UNativeWidgetHost;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMainWindowBtnDelegate, int32, BtnSelected);

UCLASS(Abstract)
class TANKOGEDON60_API UUW_MainWindow : public UUserWidget
{
	GENERATED_BODY()
	
public:

	virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;

protected:

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
	UButton* BtnNewGame;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* BtnQuit;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* AnimNewGame;

	UPROPERTY(BlueprintAssignable)
	FMainWindowBtnDelegate OnMainWindowBtnSelected;

	UFUNCTION()
	void OnBtnNewGameClicked();

	UFUNCTION()
	void OnBtnQuitClicked();

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
	UNativeWidgetHost* RadioButtonHost;
};
