// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InterfaceDamageTaker.h"
#include "ComponentHealth.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANKOGEDON60_API UComponentHealth: public UActorComponent
{
	GENERATED_BODY()

	// ����������� ����� �������
	// EVENT ����� ���� ������ �� ����� ������
	DECLARE_EVENT(UComponentHealth, FOnDeath);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeathDelegate);

	DECLARE_EVENT_OneParam(UComponentHealth, FOnDamaged, FDamageData);

	// � ������� �� EVENT ����������� ����� ������ ���� ���
	// ����� ���� ������ ������ ������
	// DECLARE_DELEGATE()
	// �� ����� ������� ����� ����������� ����� �����������, ��� �� EVENT
	// DECLARE_MULTICAST_DELEGATE()
	// ���������� UFUNCTION � ����� AddDynamic()
	// 1 ���������
	// DECLARE_DYNAMIC_DELEGATE();
	// ��������� �����������
	// DECLARE_DYNAMIC_MULTICAST_DELEGATE();

public:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = Health)
	float HealthMax = 10;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Health)
	float HealthCurrent;

	// Sets default values for this component's properties
	UComponentHealth();

	void TakeDamage(FDamageData Damage);

	// UPROPERTY(BlueprintAssignable)
	FOnDeath OnDeathEvent;
	FOnDamaged OnDamagedEvent;

	UPROPERTY(BlueprintAssignable)
	FOnDeathDelegate OnDeathDelegate;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
