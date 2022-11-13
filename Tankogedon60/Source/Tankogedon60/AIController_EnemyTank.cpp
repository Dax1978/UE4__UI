// Fill out your copyright notice in the Description page of Project Settings.


#include "AIController_EnemyTank.h"

void AAIController_EnemyTank::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	// Отпишемся
	if (TankPawn)
	{
		TankPawn->OnTargetsChaged.Remove(TargetChangedDelegateHandle);
	}

	TankPawn = Cast<APTank>(InPawn);
	if (TankPawn)
	{
		PatrollingPointTag = TankPawn->PatrollingPointTag;
	}

	RebuildWaypoints();

	TargetChangedDelegateHandle = TankPawn->OnTargetsChaged.AddUObject(this, &AAIController_EnemyTank::OnTargetsChaged);
}

void AAIController_EnemyTank::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!TankPawn || PatrollingPoints.Num() < 2)
	{
		return;
	}

	if (CurrentWaypointIndex >= PatrollingPoints.Num() || CurrentWaypointIndex < 0)
	{
		CurrentWaypointIndex = 0;
	}

	auto Point = PatrollingPoints[CurrentWaypointIndex];
	auto PointLocation = Point->GetActorLocation();
	auto Location = TankPawn->GetActorLocation();

	// Надо ли поворачивать
	auto MovementDirection = PointLocation - Location;
	MovementDirection.Normalize();
	// Угол между вектором направления к точке, и вектором куда наш танк повернут
	auto ForwardAngle = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(TankPawn->GetActorForwardVector(), MovementDirection)));
	// Угол между направлением танка в право и направлением нашей Waypoint
	auto RightAngle = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(TankPawn->GetActorRightVector(), MovementDirection)));
	// Это (2 вектора вверху) математический лайфхак, для определения куда нужно будет поворачивать
	float RotationValue = 0;
	if (ForwardAngle > 5) RotationValue = 1;
	if (RightAngle > 90) RotationValue = -RotationValue;
	// Если угол для поворота большой, то останавливаемся и поворачиваем
	if (ForwardAngle > 45)
	{
		TankPawn->MoveForward(0);
	}
	else
	{
		TankPawn->MoveForward(1);
	}

	TankPawn->RotateRight(RotationValue);

	// При приближении получаем слеующую Waypoint
	if (FVector::Dist2D(PointLocation, Location) < MovementAccuracy)
	{
		CurrentWaypointIndex++;
	}

	if (TankPawn->CanFire())
	{
		TankPawn->Shoot();
	}
}

void AAIController_EnemyTank::BeginPlay()
{
	Super::BeginPlay();

	RebuildWaypoints();
}

void AAIController_EnemyTank::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);


}

FVector AAIController_EnemyTank::GetTargetLocation() const
{
	if (!TankPawn)
	{
		return FVector::ZeroVector;
	}

	if (TankPawn->TargetCurrent.IsValid())
	{
		return TankPawn->TargetCurrent->GetActorLocation();
	};

	return TankPawn->GetActorLocation() + TankPawn->GetActorForwardVector() * 1000;
}

void AAIController_EnemyTank::RebuildWaypoints()
{
	// 1. Почистим массив PatrollingPoints
	PatrollingPoints.Empty();

	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(),
		APatrollingPoint_EnemyTank::StaticClass(),
		PatrollingPointTag,
		Actors);
	// Нужно полученный массив Actors перегнать в массив PatrollingPoints	
	// 2. Проходим по массиву и перегоняем его в массив PatrollingPoints
	// Так напрямую нельзя сделать!
	//for (auto Actor : Actors)
	//{
	//	// CastChecked - гарантированно не получим nullptr
	//	PatrollingPoints.Add(CastChecked<APatrollingPoint_EnemyTank>(Actor));
	//}
	// Добавим промежуточный массив
	TArray<APatrollingPoint_EnemyTank*> Points;
	for (auto Actor : Actors)
	{
		// CastChecked - гарантированно не получим nullptr
		Points.Add(CastChecked<APatrollingPoint_EnemyTank>(Actor));
	}
	// 3. Отсортируем массив по index
	Points.Sort([](const APatrollingPoint_EnemyTank& A, const APatrollingPoint_EnemyTank& B) {
		return A.Index > B.Index;
		});
	for (auto Actor : Points)
	{
		// CastChecked - гарантированно не получим nullptr
		PatrollingPoints.Add(Actor);
	}

	// Выведем линии между всеми собранными точками
	for (int i = 1; i < PatrollingPoints.Num(); i++)
	{
		DrawDebugLine(GetWorld(),
			PatrollingPoints[i - 1]->GetActorLocation() + FVector(0, 0, 70),
			PatrollingPoints[i]->GetActorLocation() + FVector(0, 0, 70),
			FColor::Red, false, 20);
	}
	if (PatrollingPoints.Num() > 1) {
		DrawDebugLine(GetWorld(),
			PatrollingPoints[0]->GetActorLocation() + FVector(0, 0, 70),
			PatrollingPoints[PatrollingPoints.Num() - 1]->GetActorLocation() + FVector(0, 0, 70),
			FColor::Red, false, 20);
	}

	// GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString::Printf(TEXT("RebuildWaypoints Actors %f"), Actors.Num()));
	// GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString::Printf(TEXT("RebuildWaypoints PatrollingPoints %f"), PatrollingPoints.Num()));
}

void AAIController_EnemyTank::OnTargetsChaged()
{
	if (!TankPawn)
	{
		return;
	}
	TankPawn->FindBestTarget();
}
