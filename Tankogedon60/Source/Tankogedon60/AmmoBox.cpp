// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoBox.h"

// Sets default values
AAmmoBox::AAmmoBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<UBoxComponent>("Collision");
	RootComponent = Collision;
	// Подписываемся на событие, когда с коллизией есть пересечение
	Collision->OnComponentBeginOverlap.AddDynamic(this, &AAmmoBox::OnBeginOverlapAmmobox);
	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>("BodyMesh");
	BodyMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AAmmoBox::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAmmoBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAmmoBox::OnBeginOverlapAmmobox(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto Tank = Cast<APTank>(OtherActor);
	if (Tank)
	{
		Tank->AddCannon(CannonClass);

		if (CannonClass->GetAuthoredName() == "BP_CannonTrace_C")
		{
			Tank->AddMissile(AmmoCount, ECannonType::Trace);
			// UE_LOG(LogTemp, Warning, TEXT("Trace"));
		}
		else if (CannonClass->GetAuthoredName() == "BP_CannonProjectile_C")
		{
			Tank->AddMissile(AmmoCount, ECannonType::Projectile);
			// UE_LOG(LogTemp, Warning, TEXT("Projectile"));
		}
		// FString txt = ;
		// const TCHAR* txt_tchar = *txt;
		// UE_LOG(LogTemp, Warning, TEXT("jjjjjjj: %s"), txt_tchar);
	}
}

