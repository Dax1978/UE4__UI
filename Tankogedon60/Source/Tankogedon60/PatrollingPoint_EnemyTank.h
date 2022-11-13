// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PatrollingPoint_EnemyTank.generated.h"

UCLASS()
class TANKOGEDON60_API APatrollingPoint_EnemyTank : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APatrollingPoint_EnemyTank();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Patrolling)
	int Index = -1;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
