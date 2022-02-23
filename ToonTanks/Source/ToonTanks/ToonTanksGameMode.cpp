// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"

#include "Tank.h"
#include "ToonTanksPlayerController.h"
#include "Turret.h"
#include "Kismet/GameplayStatics.h"

void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();

	HandleGameStart();
}

void AToonTanksGameMode::ActorDied(TObjectPtr<AActor> DeadActor)
{
	if (DeadActor == PlayerTankPtr)
	{
		PlayerTankPtr->HandleDestruction();
		if (PlayerControllerPtr)
		{
			PlayerControllerPtr->SetPlayerEnabledState(false);
		}

		bIsPlayerAlive = false;
		GameOver(false);
		return;
	}

	if (const auto DeadTurret = Cast<ATurret>(DeadActor))
	{
		DeadTurret->HandleDestruction();
		RemainingTurretsAmount--;
		UpdateTurretAmountOnHud();

		if(RemainingTurretsAmount == 0)
		{
			GameOver(true);
		}
	}
}

void AToonTanksGameMode::HandleGameStart()
{
	const auto PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	PlayerTankPtr = Cast<ATank>(PlayerPawn);
	PlayerControllerPtr =
		Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	StartGame();

	if (PlayerControllerPtr)
	{
		PlayerControllerPtr->SetPlayerEnabledState(false);

		FTimerHandle PlayerEnableTimerHandle;
		const auto InputDelegate = FTimerDelegate::CreateUObject(
			PlayerControllerPtr.Get(),
			&AToonTanksPlayerController::SetPlayerEnabledState,
			true);

		auto& TimerManager = GetWorld()->GetTimerManager();
		TimerManager.SetTimer(PlayerEnableTimerHandle, InputDelegate, StartDelay, false);
	}
}
