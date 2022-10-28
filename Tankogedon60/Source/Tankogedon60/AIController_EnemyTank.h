// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "PatrollingPoint_EnemyTank.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "PTank.h"
#include "Interface_TargetController.h"
#include "AIController_EnemyTank.generated.h"

/**
 * 
 */
UCLASS()
class TANKOGEDON60_API AAIController_EnemyTank : public AAIController, public IInterface_TargetController
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Patrolling)
	FName PatrollingPointTag;

	// –ассто€ние до Waypoint после которого мы переключаемс€ к следующей точке
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Patrolling)
	float MovementAccuracy = 10;

	virtual void OnPossess(APawn* InPawn) override;

	virtual void Tick(float DeltaSeconds) override;

	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual FVector GetTargetLocation() const override;

private:
	void RebuildWaypoints();
	void OnTargetsChaged();

	APTank* TankPawn;

	int CurrentWaypointIndex = 0;

	FDelegateHandle TargetChangedDelegateHandle;

	// TArray<APatrollingPoint_EnemyTank*> PatrollingPoints;
	// ƒелаем слабый указатель, нам не важно что бы все точки были живы
	TArray<TWeakObjectPtr<APatrollingPoint_EnemyTank>> PatrollingPoints;
};
