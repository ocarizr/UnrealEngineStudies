// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

ATank::ATank()
: ABasePawn()
, SpringArm(CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm")))
, Camera(CreateDefaultSubobject<UCameraComponent>(TEXT("Camera")))
, PlayerControllerPtr(nullptr)
, MovementOffset(FVector::ZeroVector)
, TurnOffset(FRotator::ZeroRotator)
{
	SpringArm->SetupAttachment(RootComponent);
	Camera->SetupAttachment(SpringArm);
}

void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	AddActorLocalOffset(MovementOffset * DeltaTime, true);
	AddActorLocalRotation(TurnOffset * DeltaTime, true);
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);
	PlayerInputComponent->BindAxis(TEXT("RotateTurret"), this, &ATank::RotateTurret);

	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::Fire);
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerControllerPtr = Cast<APlayerController>(GetController());
}

void ATank::Move(float AxisValue)
{
	MovementOffset.X = AxisValue * MovementSpeed;
}

void ATank::Turn(float AxisValue)
{
	TurnOffset.Yaw = AxisValue * TurnSpeed;
}

void ATank::RotateTurret(float AxisValue)
{
	if(PlayerControllerPtr == nullptr)
	{
		return;
	}

	// Getting the point the cursor is pointing to
	FHitResult HitResult;
	PlayerControllerPtr->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
	Super::RotateTurret(HitResult.ImpactPoint);
}

void ATank::HandleDestruction()
{
	Super::HandleDestruction();
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
}
