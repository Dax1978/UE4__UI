// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/Actor.h"
#include "Projectile.h"
#include "DrawDebugHelpers.h"
#include "InterfaceDamageTaker.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/AudioComponent.h"
#include "Cannon.generated.h"

UENUM()
enum class ECannonType
{
	Projectile,
	Trace
};


UCLASS()
class TANKOGEDON60_API ACannon : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Component)
	USceneComponent* DefaultRoot;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Component)
	UStaticMeshComponent* BodyMesh;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Component)
	UArrowComponent* PointSpawnProjectile;

	// ¬изуальные эффекты
	// „астицы
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Effect)
	UParticleSystemComponent* EffectProjectileParticle;
	// јудио выстрела
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Effect)
	UAudioComponent* EffectProjectileAudio;

	// Sets default values for this actor's properties
	ACannon();

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = Cannon)
	ECannonType CannonType = ECannonType::Projectile;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Cannon)
	float TimeReload = 1;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Cannon)
	TSubclassOf<AProjectile> ProjectileClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Cannon)
	float TraceDistance = 1000;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Movement)
	float DamageTrace = 1;

	// Ёффект дл€ обратной св€зи джойстику
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Effect)
	UForceFeedbackEffect* EffectFeedback;
	// Ёффект тр€ски камеры при выстреле
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Effect)
	TSubclassOf<UCameraShakeBase> EffectCameraShake;

	void Shoot(class APWarrior* InWarrior);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FTimerHandle TimerReload;
	void OnReload();
	bool IsReadyToShoot = true;

	class APWarrior* Warrior;
};
