// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTanksGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	UFUNCTION(Category="Custom Events", BlueprintImplementableEvent)
	void StartGame();

	UFUNCTION(Category="Custom Events", BlueprintImplementableEvent)
	void GameOver(bool bWonGame);

	UFUNCTION(Category="Custom Events", BlueprintImplementableEvent)
	void UpdateTurretAmountOnHud();

public:
	void ActorDied(TObjectPtr<AActor> DeadActor);
	
	void IncrementTurretAmount() { RemainingTurretsAmount++; }

private:
	void HandleGameStart();

private:
	TObjectPtr<class ATank> PlayerTankPtr;

	UPROPERTY(Category="Custom Data", BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<class AToonTanksPlayerController> PlayerControllerPtr;

	UPROPERTY(Category="Game Config", EditAnywhere)
	float StartDelay = 3.f;

	UPROPERTY(Category="Game Data To Track", VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	int RemainingTurretsAmount;

public:
	UPROPERTY(Category="Game Data To Track", VisibleAnywhere)
	bool bIsPlayerAlive = true;
};
