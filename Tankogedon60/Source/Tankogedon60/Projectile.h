// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "InterfaceDamageTaker.h"
#include "Projectile.generated.h"

UCLASS()
class TANKOGEDON60_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Component)
	USphereComponent* Collision;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Component)
	UStaticMeshComponent* BodyMesh;

	// Sets default values for this actor's properties
	AProjectile();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Movement)
	float KoefSpeedLine = 777;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Movement)
	float FlyDistance = 2000;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Movement)
	float Damage = 1;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	FVector StartLocation;

	UFUNCTION()
	void OnBeginOverlapProjectile(UPrimitiveComponent* OverlappedComponent, 
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, 
		bool bFromSweep, 
		const FHitResult& SweepResult);

	class APWarrior* Warrior;
};
