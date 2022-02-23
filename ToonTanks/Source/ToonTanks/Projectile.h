// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()

public:
	AProjectile();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	           UPrimitiveComponent* OtherComponent, FVector NormalImpulse,
	           const FHitResult& HitResult);

private:
	UPROPERTY(Category="Components", VisibleAnywhere)
	TObjectPtr<class UStaticMeshComponent> ProjectileMesh;

	UPROPERTY(Category="Components", VisibleAnywhere)
	TObjectPtr<class UProjectileMovementComponent> MovementComponent;

	UPROPERTY(Category="Components", VisibleAnywhere)
	TObjectPtr<class UParticleSystemComponent> SmokeTrailComponent;

	UPROPERTY(Category="Combat", EditAnywhere)
	TObjectPtr<class UParticleSystem> HitParticles;

	UPROPERTY(Category="Combat", EditAnywhere)
	TObjectPtr<class USoundBase> LaunchSound;

	UPROPERTY(Category="Combat", EditAnywhere)
	TObjectPtr<class USoundBase> HitSound;

	UPROPERTY(Category="Combat", EditAnywhere)
	TSubclassOf<class UCameraShakeBase> HitCameraShake;
	
	UPROPERTY(Category="Combat", EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	float DamageValue = 50.f;
};
