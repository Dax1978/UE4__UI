// Fill out your copyright notice in the Description page of Project Settings.


#include "PC_Tank.h"

void APC_Tank::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("Shoot", EInputEvent::IE_Pressed, this, &APC_Tank::OnShoot);
	InputComponent->BindAxis("MoveForward", this, &APC_Tank::OnMoveForward);
	InputComponent->BindAxis("MoveRight", this, &APC_Tank::OnMoveRight);
	InputComponent->BindAxis("RotateRight", this, &APC_Tank::OnRotateRight);

	SetShowMouseCursor(true);
}

void APC_Tank::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	Tank = Cast<APTank>(InPawn);
}

void APC_Tank::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// Точка на игровом поле, куда показывает курсор мыши
	if (Tank)
	{
		FVector MousePosition;
		FVector MouseDirection;
		DeprojectMousePositionToWorld(MousePosition, MouseDirection);
		auto Z = FMath::Abs(Tank->GetActorLocation().Z - MousePosition.Z);
		WorldMousePosition = MousePosition - MouseDirection * Z / MouseDirection.Z;
		// Выведем линию
		// DrawDebugLine(GetWorld(), MousePosition, WorldMousePosition, FColor::Blue, false, 2);
	}
}

FVector APC_Tank::GetTargetLocation() const
{
	return GetWorldMousePosition();
}

void APC_Tank::OnShoot()
{
	if (Tank)
	{
		Tank->Shoot();
	}
}

void APC_Tank::OnMoveForward(float Scale)
{
	if (Tank)
	{
		Tank->MoveForward(Scale);
	}
}

void APC_Tank::OnMoveRight(float Scale)
{
	if (Tank)
	{
		Tank->MoveRight(Scale);
	}
}

void APC_Tank::OnRotateRight(float Scale)
{
	if (Tank)
	{
		Tank->RotateRight(Scale);
	}
}
