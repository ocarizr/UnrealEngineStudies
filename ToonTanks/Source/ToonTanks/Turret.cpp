// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"

#include "Tank.h"
#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"

ATurret::ATurret()
: ABasePawn()
, PlayerTankPtr(nullptr)
{
}

void ATurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const auto GameMode = Cast<AToonTanksGameMode>(UGameplayStatics::GetGameMode(this));
	if(PlayerTankPtr == nullptr || !GameMode->bIsPlayerAlive)
	{
		if(FireTimer.IsValid())
		{
			GetWorldTimerManager().ClearTimer(FireTimer);
		}
		
		return;
	}
	
	const auto PlayerLocation = PlayerTankPtr->GetActorLocation();
	const auto Distance = FVector::Dist(GetActorLocation(), PlayerLocation);

	// Track the Player Tank
	if(Distance > TrackRange)
	{
		return;
	}
	
	RotateTurret(PlayerLocation);

	// Check if can shot the Player
	auto& TimerManager = GetWorldTimerManager();
	if(Distance > FireRange)
	{
		if(FireTimer.IsValid())
		{
			TimerManager.ClearTimer(FireTimer);
		}
		
		return;
	}

	if(!FireTimer.IsValid())
	{
		TimerManager.SetTimer(FireTimer, this, &ATurret::Fire, FireRate, true, 0.f);
	}
}

void ATurret::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerTankPtr = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	
	if(const auto GameMode = Cast<AToonTanksGameMode>(UGameplayStatics::GetGameMode(this)))
	{
		GameMode->IncrementTurretAmount();
	}
}

void ATurret::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}
