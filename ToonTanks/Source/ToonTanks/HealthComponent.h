// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TOONTANKS_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void DamageTaken(AActor* DamagedActor, float Damage,
	                 const UDamageType* DamageType, AController* Instigator,
	                 AActor* DamageCauser);

private:
	UPROPERTY(Category="Data", EditAnywhere)
	float MaxHealth = 100.f;

	UPROPERTY(Category="Data", VisibleAnywhere)
	float Health = 0.f;

	UPROPERTY(Category="GameMode", EditAnywhere)
	TObjectPtr<class AToonTanksGameMode> ToonTanksGameModePtr;
};
