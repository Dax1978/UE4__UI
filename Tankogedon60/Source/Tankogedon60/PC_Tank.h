// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PTank.h"
#include "DrawDebugHelpers.h" // Для DrawDebugLine()
#include "GameFramework/PlayerController.h"
#include "Interface_TargetController.h"
#include "PC_Tank.generated.h"

/**
 * 
 */
UCLASS()
class TANKOGEDON60_API APC_Tank : public APlayerController, public IInterface_TargetController
{
	GENERATED_BODY()
		
public:
	virtual void SetupInputComponent() override;

	virtual void OnPossess(APawn* InPawn) override;

	virtual void Tick(float DeltaSeconds) override;

	FVector GetWorldMousePosition() const
	{
		return WorldMousePosition;
	}

	virtual FVector GetTargetLocation() const override;
	
private:
	void OnShoot();

	void OnMoveForward(float Scale);

	void OnMoveRight(float Scale);

	void OnRotateRight(float Scale);

	APTank* Tank = nullptr;

	// Для записи курсора мыши
	FVector WorldMousePosition;

};
