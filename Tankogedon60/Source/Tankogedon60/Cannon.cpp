// Fill out your copyright notice in the Description page of Project Settings.


#include "Cannon.h"
#include "PWarrior.h"

// Sets default values
ACannon::ACannon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultRoot = CreateDefaultSubobject<UStaticMeshComponent>("DefaultRoot");
	RootComponent = DefaultRoot;
	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>("BodyMesh");
	BodyMesh->SetupAttachment(RootComponent);
	PointSpawnProjectile = CreateDefaultSubobject<UArrowComponent>("PointSpawnProjectile");
	PointSpawnProjectile->SetupAttachment(RootComponent);

	EffectProjectileParticle = CreateDefaultSubobject<UParticleSystemComponent>("EffectProjectileParticle");
	EffectProjectileParticle->SetupAttachment(RootComponent);
	EffectProjectileAudio = CreateDefaultSubobject<UAudioComponent>("EffectProjectileAudio");
	EffectProjectileAudio->SetupAttachment(RootComponent);
}

void ACannon::Shoot(class APWarrior* InWarrior)
{
	Warrior = Cast<APWarrior>(InWarrior);
	if (!Warrior)
	{
		return;
	}

	if (!Warrior->IsAlive)
	{
		return;
	}

	if (!IsReadyToShoot)
	{
		return;
	}

	switch (CannonType)
	{
		case ECannonType::Projectile:
			// ���� �������� ������ ���, �� � ���������� �� �����
			if (Warrior->CannonCountProjectile < 1)
			{
				GEngine->AddOnScreenDebugMessage(70003, 2, FColor::Red, FString::Printf(TEXT("There are no projectile")));
				return;
			}
			// GEngine->AddOnScreenDebugMessage(70001, 2, FColor::Red, FString::Printf(TEXT("Projectile")));
			// GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString::Printf(TEXT("Projectile")));
			if (ProjectileClass)
			{
				// ������������ ���� ����� � �����
				FActorSpawnParameters SpawnParameters;
				SpawnParameters.Owner = this;
				SpawnParameters.Instigator = GetInstigator();

				auto Transform = PointSpawnProjectile->GetComponentTransform();
				// GetWorld()->SpawnActor(ProjectileClass, &Transform);
				GetWorld()->SpawnActor(ProjectileClass, &Transform, SpawnParameters);

				// ��� ������� ���������� � ������ ������ �������, �.�. ����� �� ���������
				EffectProjectileParticle->ActivateSystem();
				EffectProjectileAudio->Play();

				// ��� ������� �������� ����� ��������� � ������ �������� ��� ��������
				// 1. ������� ����������
				auto Controller = Cast<APlayerController>(GetInstigatorController());
				if (Controller)
				{
					Controller->ClientPlayForceFeedback(EffectFeedback);
					if (EffectCameraShake) 
						Controller->ClientPlayCameraShake(EffectCameraShake);
				}
			}
			
			Warrior->CannonCountProjectile -= 1;
			GEngine->AddOnScreenDebugMessage(70003, 2, FColor::Red, FString::Printf(TEXT("Projectile remained is %d"), Warrior->CannonCountProjectile));
			break;
		
		case ECannonType::Trace:
			// ���� ������� ������ ���, �� � ���������� �� �����
			if (Warrior->CannonCountTrace < 1)
			{
				GEngine->AddOnScreenDebugMessage(70003, 2, FColor::Red, FString::Printf(TEXT("There are no trace")));
				return;
			}
			// GEngine->AddOnScreenDebugMessage(70001, 2, FColor::Red, FString::Printf(TEXT("Trace")));
			// GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString::Printf(TEXT("Trace")));

			FHitResult HitResult;
			FCollisionQueryParams Params;
			Params.AddIgnoredActor(this);
			Params.AddIgnoredActor(GetInstigator());
			Params.bTraceComplex = true; // ��� �������, ����� � ����� �� ����������� ������� � ������ � ������
			auto TracePointStart = PointSpawnProjectile->GetComponentLocation();
			auto TracePointEnd = PointSpawnProjectile->GetComponentLocation() + PointSpawnProjectile->GetForwardVector() * TraceDistance;

			DrawDebugLine(GetWorld(), TracePointStart, TracePointEnd, FColor::Yellow, false, 0.5f);

			if (GetWorld()->LineTraceSingleByChannel(HitResult, TracePointStart, TracePointEnd, ECollisionChannel::ECC_Visibility, Params))
			{
				if (HitResult.Actor.IsValid())
				{
					APWarrior* WarriorTarget = Cast<APWarrior>(HitResult.Actor);
					if (WarriorTarget)
					{
						auto Damagable = Cast<IInterfaceDamageTaker>(HitResult.Actor);
						if (Damagable)
						{
							FDamageData Data;
							Data.DamageMaker = this;
							Data.DamageValue = DamageTrace;
							Data.Instigator = GetInstigator();
							Damagable->TakeDamage(Data);
							// WarriorTarget->IsAlive = false;
							// GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Yellow, FString::Printf(TEXT("Trace")));
						}						
					}
					else
					{
						HitResult.Actor->Destroy();
					}
				}
			}

			// ����� ������� ������ ������� ����� �������� - FCollisionShape &CollisionShape
			// GetWorld()->SweepSingleByChannel()
			// ����������� ����������� �����
			// GetWorld()->LineTraceTestByChannel()			

			Warrior->CannonCountTrace -= 1;
			GEngine->AddOnScreenDebugMessage(70003, 2, FColor::Red, FString::Printf(TEXT("Trace remained is %d"), Warrior->CannonCountTrace));
			break;
	}

	IsReadyToShoot = false;
	GetWorldTimerManager().SetTimer(TimerReload, this, &ACannon::OnReload, TimeReload);
}

// Called when the game starts or when spawned
void ACannon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACannon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// ������� ������� �������� �� �����������
	GEngine->AddOnScreenDebugMessage(70002, -1, FColor::Blue,
		FString::Printf(TEXT("Reload in %f seconds"), GetWorldTimerManager().GetTimerRemaining(TimerReload)));
}

void ACannon::OnReload()
{
	IsReadyToShoot = true;
}

