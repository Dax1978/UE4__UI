// Fill out your copyright notice in the Description page of Project Settings.


#include "PTurret.h"

// Sets default values
APTurret::APTurret()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APTurret::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Targeting();
	if (Cannon && CanFire())
	{
		Cannon->Shoot(this);
	}
}

// Called to bind functionality to input
void APTurret::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

