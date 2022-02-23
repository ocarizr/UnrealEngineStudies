// Fill out your copyright notice in the Description page of Project Settings.

#include "BasePawn.h"

#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"

// Sets default values
ABasePawn::ABasePawn()
: CapsuleComponent(CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Component")))
, BaseMesh(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh")))
, TurretMesh(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh")))
, ProjectileSpawnPoint(CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point")))
, TurretRotationYawOffset(0.f)
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SetRootComponent(CapsuleComponent);
	
	BaseMesh->SetupAttachment(CapsuleComponent);
	TurretMesh->SetupAttachment(BaseMesh);
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);
}

// Called every frame
void ABasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	// Smoothly make the Turret look at the target
	const auto CurrentRotation = TurretMesh->GetComponentRotation();
	const auto ToRotator = FMath::Lerp(CurrentRotation, TurretRotationYawOffset, DeltaTime * TurretRotationRate);
	TurretMesh->SetWorldRotation(ToRotator);
}

void ABasePawn::BeginPlay()
{
	Super::BeginPlay();

	TurretRotationYawOffset = TurretMesh->GetComponentRotation();
}

void ABasePawn::RotateTurret(const FVector& Target)
{
	const auto VectorToTarget = Target - TurretMesh->GetComponentLocation();
	TurretRotationYawOffset = FRotator(0.f, VectorToTarget.Rotation().Yaw, 0.f);
}

void ABasePawn::Fire()
{
	const auto Location = ProjectileSpawnPoint->GetComponentLocation();
	const auto Rotation = ProjectileSpawnPoint->GetComponentRotation();
	const auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, Location, Rotation);
	Projectile->SetOwner(this);
}

void ABasePawn::HandleDestruction()
{
	if(DeathParticles)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticles, GetActorLocation(), GetActorRotation());
	}

	if(DeathSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());
	}

	if(DeathCameraShake)
	{
		const auto PlayerController = UGameplayStatics::GetPlayerController(this, 0);
		PlayerController->ClientStartCameraShake(DeathCameraShake);
	}
}
