// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BasePawn.h"
#include "Turret.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATurret : public ABasePawn
{
	GENERATED_BODY()

public:
	ATurret();
	
	virtual void Tick(float DeltaTime) override;

	virtual void HandleDestruction() override;

protected:
	virtual void BeginPlay() override;

private:
	FTimerHandle FireTimer;
	
	TObjectPtr<class ATank> PlayerTankPtr;
	
	UPROPERTY(Category="Combat", EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	float TrackRange = 700.f;
	
	UPROPERTY(Category="Combat", EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	float FireRange = 400.f;

	UPROPERTY(Category="Combat", EditAnywhere, BlueprintReadOnly,
		meta=(AllowPrivateAccess="true", ToolTip="The amount of seconds between each shot."))
	float FireRate = 2.f;
};
