// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "PWarrior.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<USphereComponent>("Collision");
	RootComponent = Collision;
	// Подписываемся на событие, когда наш снаряд врезается во что-то
	Collision->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnBeginOverlapProjectile);

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>("BodyMesh");
	BodyMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	StartLocation = GetActorLocation();
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Здесь добавляем движение
	// Практически как только спавнится Projectile он начинает двигаться
	auto Location = GetActorLocation() + GetActorForwardVector() * KoefSpeedLine * DeltaTime;
	SetActorLocation(Location, true);

	if (FVector::DistXY(StartLocation, GetActorLocation()) > FlyDistance)
	{
		Destroy();
	}
}

void AProjectile::OnBeginOverlapProjectile(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == this || GetInstigator() == OtherActor)
	{
		return;
	}

	if (OtherActor)
	{
		Warrior = Cast<APWarrior>(OtherActor);

		if (Warrior)
		{
			auto Damagable = Cast<IInterfaceDamageTaker>(OtherActor);
			if (Damagable)
			{
				FDamageData Data;
				Data.DamageMaker = this;
				Data.DamageValue = Damage;
				Data.Instigator = GetInstigator();
				Damagable->TakeDamage(Data);
				// Warrior->IsAlive = false;
			}			
		}
		else
		{
			OtherActor->Destroy();
		}		
	}

	Destroy();
}

