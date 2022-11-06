// Fill out your copyright notice in the Description page of Project Settings.


#include "UW_MainWindow.h"
#include "Components/Button.h"
#include "SSRadioButtonsList.h"


void UUW_MainWindow::NativeConstruct()
{
	Super::NativeConstruct();

	if (BtnNewGame)
	{
		BtnNewGame->OnPressed.AddDynamic(this, &ThisClass::OnBtnNewGameClicked);
	}

	if (BtnQuit)
	{
		BtnQuit->OnPressed.AddDynamic(this, &ThisClass::OnBtnQuitClicked);
	}

	if (RadioButtonHost)
	{
		RadioButtonHost->SetContent(SNew(SSRadioButtonsList));
	}
}

void UUW_MainWindow::NativeDestruct()
{
	if (BtnNewGame)
	{
		BtnNewGame->OnPressed.RemoveAll(this);
	}

	if (BtnQuit)
	{
		BtnQuit->OnPressed.RemoveAll(this);
	}

	Super::NativeDestruct();
}

void UUW_MainWindow::OnBtnNewGameClicked()
{
	if (AnimNewGame)
	{
		PlayAnimation(AnimNewGame);
	}

	OnMainWindowBtnSelected.Broadcast(0);
}

void UUW_MainWindow::OnBtnQuitClicked()
{
	// GEngine->Exec(GetWorld(), TEXT("Quit"));
	OnMainWindowBtnSelected.Broadcast(1);
}
