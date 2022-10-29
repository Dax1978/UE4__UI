// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PWarrior.h"
#include "PTurret.generated.h"

UCLASS()
class TANKOGEDON60_API APTurret : public APWarrior
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APTurret();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
