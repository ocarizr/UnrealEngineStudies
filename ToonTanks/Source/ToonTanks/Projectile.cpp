// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AProjectile::AProjectile()
: ProjectileMesh(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh")))
, MovementComponent(CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement Component")))
, SmokeTrailComponent(CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Smoke Trail Component")))
{
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(ProjectileMesh);

	MovementComponent->InitialSpeed = 1000.f;
	MovementComponent->MaxSpeed = 1700.f;
	MovementComponent->bRotationFollowsVelocity = true;

	SmokeTrailComponent->SetupAttachment(ProjectileMesh);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);

	if(LaunchSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, LaunchSound, GetActorLocation());
	}
}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
                        UPrimitiveComponent* OtherComponent, FVector NormalImpulse,
                        const FHitResult& HitResult)
{
	const auto CurrentOwner = GetOwner();
	if(OtherActor == nullptr || OtherActor == this || OtherActor == CurrentOwner)
	{
		Destroy();
		return;
	}
	
	const auto DamageInstigator = CurrentOwner ? CurrentOwner->GetInstigatorController() : nullptr;
	UGameplayStatics::ApplyDamage(OtherActor, DamageValue, DamageInstigator, this, UDamageType::StaticClass());

	// Location to Spawn the Particle System of the Projectile Hit
	const auto& HitLocation = HitResult.Location;
	if(HitParticles)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, HitParticles, HitLocation);
	}

	if(HitSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, HitSound, HitLocation);
	}

	if(HitCameraShake)
	{
		const auto Controller = UGameplayStatics::GetPlayerController(this, 0);
		Controller->ClientStartCameraShake(HitCameraShake);
	}
	
	Destroy();
}
