// Fill out your copyright notice in the Description page of Project Settings.


#include "ComponentHealth.h"

// Sets default values for this component's properties
UComponentHealth::UComponentHealth()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	HealthCurrent = HealthMax;
}


// Called when the game starts
void UComponentHealth::BeginPlay()
{
	Super::BeginPlay();

	HealthCurrent = HealthMax;
	
}


// Called every frame
void UComponentHealth::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UComponentHealth::TakeDamage(FDamageData Damage)
{
	auto HealthPrev = HealthCurrent;
	HealthCurrent -= Damage.DamageValue;
	if (HealthCurrent < 0)
	{
		HealthCurrent = 0;
	}

	if (HealthCurrent != HealthPrev)
	{
		// Рассылаем событие всем его подписчикам
		OnDamagedEvent.Broadcast(Damage);
		if (HealthCurrent <= 0)
		{
			OnDeathEvent.Broadcast();
			OnDeathDelegate.Broadcast();
		}
	}
}