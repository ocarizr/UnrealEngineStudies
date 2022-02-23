// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	ABasePawn();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	
	UFUNCTION(Category="Combat", BlueprintCallable)
	void RotateTurret(const FVector& Target);

	UFUNCTION(Category="Combat", BlueprintCallable)
	void Fire();
	
	UFUNCTION(Category="Lifetime", BlueprintCallable)
	virtual void HandleDestruction();
	
private:
	UPROPERTY(Category="Components", VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<class UCapsuleComponent> CapsuleComponent;

	UPROPERTY(Category="Components", VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<class UStaticMeshComponent> BaseMesh;

	UPROPERTY(Category="Components", VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<class UStaticMeshComponent> TurretMesh;

	UPROPERTY(Category="Components", VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<class USceneComponent> ProjectileSpawnPoint;

	UPROPERTY(Category="Combat", EditAnywhere)
	TObjectPtr<class UParticleSystem> DeathParticles;

	UPROPERTY(Category="Combat", EditAnywhere)
	TObjectPtr<class USoundBase> DeathSound;
	
	UPROPERTY(Category="Combat", EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(Category="Combat", EditAnywhere)
	TSubclassOf<class UCameraShakeBase> DeathCameraShake;
	
	FRotator TurretRotationYawOffset;

	UPROPERTY(Category="Combat", EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	float TurretRotationRate = 30.f;
};
