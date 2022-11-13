// Fill out your copyright notice in the Description page of Project Settings.


#include "PatrollingPoint_EnemyTank.h"

// Sets default values
APatrollingPoint_EnemyTank::APatrollingPoint_EnemyTank()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void APatrollingPoint_EnemyTank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APatrollingPoint_EnemyTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

