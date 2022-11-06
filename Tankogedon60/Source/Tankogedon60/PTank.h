// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PWarrior.h"
#include "CoreMinimal.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Tankogedon60.h"
#include "Kismet/KismetSystemLibrary.h" // для выхода из игры
#include "PTank.generated.h"

UCLASS()
class TANKOGEDON60_API APTank : public APWarrior
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Component)
	USpringArmComponent* Arm;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Component)
	UCameraComponent* Camera;

	// Sets default values for this pawn's properties
	APTank();

	void MoveForward(float Scale);
	void MoveRight(float Scale);
	void RotateRight(float Scale);

	virtual void PossessedBy(AController* NewController) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Movement)
	float KoefSpeedLine = 500;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Movement)
	float KoefSpeedLineAcceleration = 0.1f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Movement)
	float KoefSpeedRotate = 77;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Movement)
	float KoefSpeedRotateAcceleration = 0.2f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Patrolling)
	FName PatrollingPointTag;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Destroed();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	float MoveForwardScale = 0;
	float MoveForwardScaleCurrent = 0;
	float MoveRightScale = 0;
	float MoveRightScaleCurrent = 0;
	float RotateRightScale = 0;
	float RotateRightScaleCurrent = 0;
	// class APC_Tank* TankController;
	class IInterface_TargetController* TankController;

};
