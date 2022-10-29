// Fill out your copyright notice in the Description page of Project Settings.


#include "PTank.h"
#include "PC_Tank.h"

// Sets default values
APTank::APTank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Arm = CreateDefaultSubobject<USpringArmComponent>("Arm");
	Arm->SetupAttachment(RootComponent);
	Arm->bInheritPitch = false;
	Arm->bInheritRoll = false;
	Arm->bInheritYaw = false;
	Arm->bDoCollisionTest = false;
	Arm->TargetArmLength = 777;	
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(Arm);
}

void APTank::MoveForward(float Scale)
{
	if (IsAlive)
	{
		MoveForwardScale = Scale;
	}
	else
	{
		MoveForwardScale = 0.0f;
	}	
}

void APTank::MoveRight(float Scale)
{
	if (IsAlive)
	{
		MoveRightScale = Scale;
	}
	else
	{
		MoveRightScale = 0.0f;
	}
}

void APTank::RotateRight(float Scale)
{
	if (IsAlive)
	{
		RotateRightScale = Scale;
	}
	else
	{
		RotateRightScale = 0.0f;
	}
}

void APTank::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// TankController = Cast<APC_Tank>(NewController);
	TankController = Cast<IInterface_TargetController>(NewController);
}

// Called when the game starts or when spawned
void APTank::BeginPlay()
{
	Super::BeginPlay();
	
}

void APTank::Destroed()
{
	//if (Cannon)
	//{
	//	// ����� ������������ ���� ����������� �������, �� ����������� ����� �� ����� ����
	//	// 1. ���������� ����������, ��� ��� ���������� ������
	//	auto PlayerController = Cast<APC_Tank>(GetController());
	//	// 2. ���� ���������� ������, �� ����������� ����� �� ����		
	//	if (PlayerController)
	//	{
	//		FGenericPlatformMisc::RequestExit(false);
	//	}
	//}
}

// Called every frame
void APTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// �������� ������ � ����
	// ���� ���������
	MoveForwardScaleCurrent = FMath::Lerp(MoveForwardScaleCurrent, MoveForwardScale, KoefSpeedLineAcceleration);
	MoveRightScaleCurrent = FMath::Lerp(MoveRightScaleCurrent, MoveRightScale, KoefSpeedLineAcceleration);
	// ���� ��������
	auto Location = GetActorLocation() +
		GetActorForwardVector() * MoveForwardScaleCurrent * KoefSpeedLine * DeltaTime +
		GetActorRightVector() * MoveRightScaleCurrent * KoefSpeedLine * DeltaTime;
	SetActorLocation(Location, true);

	// �����������
	// UE_LOG(LogTemp, Warning, TEXT("Acceleration %f"), MoveRightScaleCurrent);
	// UE_LOG(LogTank, Warning, TEXT("Acceleration %f"), MoveRightScaleCurrent);

	// �������
	// ���� ���������
	RotateRightScaleCurrent = FMath::Lerp(RotateRightScaleCurrent, RotateRightScale, KoefSpeedRotateAcceleration);
	// ���� ��������
	auto Rotation = GetActorRotation();
	Rotation.Yaw = Rotation.Yaw + RotateRightScaleCurrent * KoefSpeedRotate * DeltaTime;
	SetActorRotation(Rotation);

	// ������� ����� �� ���������� ����
	if (TankController)
	{
		// auto MousePosition = TankController->GetWorldMousePosition();
		auto MousePosition = TankController->GetTargetLocation();
		// auto Rotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), MousePosition);
		auto TurretRotation = UKismetMathLibrary::FindLookAtRotation(TurretMesh->GetComponentLocation(), MousePosition);
		auto TurretRotationCurrent = TurretMesh->GetComponentRotation();
		TurretRotation.Pitch = TurretRotationCurrent.Pitch;
		TurretRotation.Roll = TurretRotationCurrent.Roll;
		TurretRotationCurrent = FMath::Lerp(TurretRotationCurrent, TurretRotation, KoefTurretSpeedRotateAcceleration);
		TurretMesh->SetWorldRotation(TurretRotationCurrent);
		DrawDebugLine(GetWorld(),
			CannonAttachment->GetComponentLocation(),
			CannonAttachment->GetComponentLocation() + CannonAttachment->GetForwardVector() * 1000,
			FColor::Green, false, -1, 0, 3);
	}

	if (!IsAlive)
	{
		// ����� ������������ ���� ����������� �������, �� ����������� ����� �� ����� ����
		// 1. ���������� ����������, ��� ��� ���������� ������
		auto PlayerController = Cast<APC_Tank>(GetController());
		// 2. ���� ���������� ������, �� ����������� ����� �� ����		
		if (PlayerController)
		{
			// ������ ������ ������� �� UE
			// FGenericPlatformMisc::RequestExit(false);

			// ����� ������ ���������� ����

			// UKismetSystemLibrary::QuitGame(GetWorld(), PlayerController, EQuitPreference::Quit, false);
		}
	}
}

// Called to bind functionality to input
void APTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

