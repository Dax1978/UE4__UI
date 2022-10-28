// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Cannon.h"
#include "Kismet/KismetMathLibrary.h"
#include "InterfaceDamageTaker.h"
#include "ComponentHealth.h"
#include "PWarrior.generated.h"

UENUM()
enum class EClan
{
	Our,
	Enemy
};

UCLASS()
class TANKOGEDON60_API APWarrior : public APawn, public IInterfaceDamageTaker
{
	GENERATED_BODY()


	// EVENT для вражеского танка, что бы находил цели
	DECLARE_EVENT(APWarrior, FOnTargetsChaged);

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Component)
	UBoxComponent* Collision;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=Component)
	UStaticMeshComponent* BodyMesh;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Component)
	UStaticMeshComponent* TurretMesh;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Component)
	UArrowComponent* CannonAttachment;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Component)
	USphereComponent* TargetRange;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Component)
	UComponentHealth* ComponentHealth;

	// Sets default values for this pawn's properties
	APWarrior();

	void Shoot();
	void AddMissile(int MissileCount = 27, ECannonType CannonType = ECannonType::Projectile);
	void AddCannon(TSubclassOf<ACannon> InCannonClass);

	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Cannon)
	TSubclassOf<ACannon> CannonClass;
	// Количество Projectile
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Cannon)
	int CannonCountProjectile = 37;
	// Количество Projectile
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Cannon)
	int CannonCountTrace = 100;
	// Жив ли
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Game)
	bool IsAlive = true;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Game)
	EClan Clan = EClan::Our;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Game)
	float KoefTurretSpeedRotateAcceleration = 0.1f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Game)
	float AccuracyFire = 5.0f;

	UPROPERTY()
	ACannon* Cannon;

	FOnTargetsChaged OnTargetsChaged;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Destroed();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void TakeDamage(FDamageData Damage) override;

	TArray<TWeakObjectPtr<AActor>> Targets;
	TWeakObjectPtr<AActor> TargetCurrent;
	void Targeting();
	bool CanFire();

	void OnDamaged(FDamageData Damage);

	UFUNCTION(BlueprintCallable)
	void OnDeath();
	UFUNCTION(BlueprintCallable)
	void OnDeathDelegate();

	const TArray<TWeakObjectPtr<AActor>>& GetPossibleTargets() const {
		return Targets;
	}

	void FindBestTarget();

private:
	UFUNCTION()
	void OnBeginOverlapTargetrange(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlapTargetrange(UPrimitiveComponent* OverlappedComp, 
		AActor* Other, 
		UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex);	
};
