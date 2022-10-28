// Fill out your copyright notice in the Description page of Project Settings.


#include "PWarrior.h"



// Sets default values
APWarrior::APWarrior()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<UBoxComponent>("Collision");
	RootComponent = Collision;
	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>("BodyMesh");
	BodyMesh->SetupAttachment(RootComponent);
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>("TurretMesh");
	TurretMesh->SetupAttachment(BodyMesh);
	CannonAttachment = CreateDefaultSubobject<UArrowComponent>("CannonAttachment");
	CannonAttachment->SetupAttachment(TurretMesh);
	TargetRange = CreateDefaultSubobject<USphereComponent>("TargetRange");
	TargetRange->SetupAttachment(Collision);
	// Подписываемся на событие, когда с TargetRange есть пересечение
	TargetRange->OnComponentBeginOverlap.AddDynamic(this, &APWarrior::OnBeginOverlapTargetrange);
	TargetRange->OnComponentEndOverlap.AddDynamic(this, &APWarrior::OnEndOverlapTargetrange);

	ComponentHealth = CreateDefaultSubobject<UComponentHealth>("ComponentHealth");
	// подписываемся на события
	ComponentHealth->OnDamagedEvent.AddUObject(this, &APWarrior::OnDamaged);
	ComponentHealth->OnDeathEvent.AddUObject(this, &APWarrior::OnDeath);
	// ComponentHealth->OnDeathDelegate.AddDynamic(this, );

}

void APWarrior::Shoot()
{
	if (Cannon)
	{
		Cannon->Shoot(this);
	}
}

void APWarrior::AddMissile(int MissileCount, ECannonType CannonType)
{
	switch (CannonType)
	{
		case ECannonType::Projectile:
			CannonCountProjectile += MissileCount;
			break;
		case ECannonType::Trace:
			CannonCountTrace += MissileCount;
			break;
	}
}

void APWarrior::AddCannon(TSubclassOf<ACannon> InCannonClass)
{
	// Если пушка уже была, старую надо уничтожить
	if (Cannon)
	{
		Cannon->Destroy();
		Cannon = nullptr;
	}

	// Спавним пушку
	if (InCannonClass)
	{
		// Пробрасываем Павн бойца в пушку
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.Owner = this;
		SpawnParameters.Instigator = this;

		// Cannon = GetWorld()->SpawnActor<ACannon>(CannonClass);
		Cannon = GetWorld()->SpawnActor<ACannon>(InCannonClass, SpawnParameters);
		Cannon->AttachToComponent(CannonAttachment, FAttachmentTransformRules::SnapToTargetIncludingScale);
	}
}

// Called when the game starts or when spawned
void APWarrior::BeginPlay()
{
	Super::BeginPlay();

	AddCannon(CannonClass);
}

void APWarrior::Destroed()
{
	if (Cannon)
	{
		Cannon->Destroy();
	}
}

// Called every frame
void APWarrior::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APWarrior::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APWarrior::TakeDamage(FDamageData Damage)
{
	ComponentHealth->TakeDamage(Damage);
}

void APWarrior::OnBeginOverlapTargetrange(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!this->IsAlive)
	{
		return;
	}

	if (OtherActor == this || OtherActor == GetInstigator() || OtherActor == nullptr)
	{
		return;
	}

	if (!OtherActor->IsA<APWarrior>())
	{
		return;
	}

	auto WarriorActor = Cast<APWarrior>(OtherActor);
	if (WarriorActor)
	{
		if (this->Clan == WarriorActor->Clan)
		{
			return;
		}

		Targets.Add(OtherActor);
		OnTargetsChaged.Broadcast();
		FindBestTarget();
	}	
}

void APWarrior::OnEndOverlapTargetrange(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!this->IsAlive)
	{
		return;
	}

	if (OtherActor == this || OtherActor == GetInstigator() || OtherActor == nullptr)
	{
		return;
	}

	if (!OtherActor->IsA<APWarrior>())
	{
		return;
	}

	Targets.Remove(OtherActor);

	if (OtherActor == TargetCurrent)
	{
		OnTargetsChaged.Broadcast();
		FindBestTarget();
	}	
}

void APWarrior::FindBestTarget()
{
	float MinDistance = 100000000000;
	auto Location = GetActorLocation();
	AActor* TargetBest = nullptr;
	for (auto Target : Targets)
	{
		if (Target.IsValid())
		{
			auto Distance = FVector::DistXY(Location, Target->GetActorLocation());
			if (Distance < MinDistance)
			{
				MinDistance = Distance;
				TargetBest = Target.Get();
			}
		}		
	}

	TargetCurrent = TargetBest;
}

void APWarrior::Targeting()
{
	if (!TargetCurrent.IsValid())
	{
		return;
	}
	
	auto TurretRotation = UKismetMathLibrary::FindLookAtRotation(TurretMesh->GetComponentLocation(), TargetCurrent->GetActorLocation());	
	auto TurretRotationCurrent = TurretMesh->GetComponentRotation();
	TurretRotation.Pitch = TurretRotationCurrent.Pitch;
	TurretRotation.Roll = TurretRotationCurrent.Roll;
	TurretRotationCurrent = FMath::Lerp(TurretRotationCurrent, TurretRotation, KoefTurretSpeedRotateAcceleration);
	TurretMesh->SetWorldRotation(TurretRotationCurrent);
}

bool APWarrior::CanFire()
{
	if (!TargetCurrent.IsValid())
	{
		return false;
	}

	auto TurretRotation = UKismetMathLibrary::FindLookAtRotation(TurretMesh->GetComponentLocation(), TargetCurrent->GetActorLocation());
	auto TurretRotationCurrent = TurretMesh->GetComponentRotation();
	if (FMath::Abs(TurretRotation.Yaw - TurretRotationCurrent.Yaw) < AccuracyFire)
	{
		// Проверяем, а видим ли мы чужой танк?
		FHitResult HitResult;
		FCollisionQueryParams Params;
		Params.bTraceComplex = true; // Это костыль, иначе у трейс не срабатывает колизия с танком и башней
		if (GetWorld()->LineTraceSingleByChannel(HitResult, 
			this->CannonAttachment->GetComponentLocation(),
			TargetCurrent->GetActorLocation(),
			ECollisionChannel::ECC_Visibility, 
			Params))
		{
			// Если лучем действительно попадаем в нашу цель, а не в объект между нами и нашей целью
			// Т.е. нет преград между нами
			if (HitResult.Actor == TargetCurrent)
			{
				return true;
			}
		}		
	}

	return false;
}

void APWarrior::OnDamaged(FDamageData Damage)
{
	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, FString::Printf(TEXT("Health %f"), ComponentHealth->HealthCurrent));
}

void APWarrior::OnDeath()
{
	IsAlive = false;
	//// Когда уничтожается танк управляемый игроком, мы запрашиваем выход из нашей игры
	//	// 1. Определяем контроллер, что это контроллер игрока
	//auto PlayerController = Cast<APC_Tank>(GetController());
	//// 2. Если контроллер игрока, то запрашиваем выход из игры		
	//if (PlayerController)
	//{
	//	FGenericPlatformMisc::RequestExit(false);
	//}
}

void APWarrior::OnDeathDelegate()
{

}
