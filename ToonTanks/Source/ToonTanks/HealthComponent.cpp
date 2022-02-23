// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);
	ToonTanksGameModePtr = Cast<AToonTanksGameMode>(UGameplayStatics::GetGameMode(this));
}

void UHealthComponent::DamageTaken(AActor* DamagedActor, float Damage,
                                   const UDamageType* DamageType, AController* Instigator,
                                   AActor* DamageCauser)
{
	if(Damage <= 0.f)
	{
		return;
	}
	
	Health = FMath::Clamp(Health - Damage, 0.f, MaxHealth);

	if(Health == 0.f && ToonTanksGameModePtr)
	{
		ToonTanksGameModePtr->ActorDied(DamagedActor);
	}
}
