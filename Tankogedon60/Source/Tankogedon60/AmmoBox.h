// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Cannon.h"
#include "PTank.h"
#include "AmmoBox.generated.h"

UCLASS()
class TANKOGEDON60_API AAmmoBox : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Component)
	UBoxComponent* Collision;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Component)
	UStaticMeshComponent* BodyMesh;

	// Sets default values for this actor's properties
	AAmmoBox();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Component)
	TSubclassOf<ACannon> CannonClass;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Component)
	int AmmoCount = 17;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void OnBeginOverlapAmmobox(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);
};
