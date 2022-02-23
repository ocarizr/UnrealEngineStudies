// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:
	ATank();
	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void HandleDestruction() override;

protected:
	virtual void BeginPlay() override;
	
private:
	UFUNCTION(Category="Movement", BlueprintCallable)
	void Move(float AxisValue);

	UFUNCTION(Category="Movement", BlueprintCallable)
	void Turn(float AxisValue);
	
	void RotateTurret(float AxisValue);

private:
	UPROPERTY(Category="Components", VisibleAnywhere)
	TObjectPtr<class USpringArmComponent> SpringArm;

	UPROPERTY(Category="Components", VisibleAnywhere)
	TObjectPtr<class UCameraComponent> Camera;

	TObjectPtr<APlayerController> PlayerControllerPtr;

	UPROPERTY(Category="Movement", EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess="true"))
	float MovementSpeed = 200.f;

	UPROPERTY(Category="Movement", EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess="true"))
	float TurnSpeed = 30.f;
	
	FVector MovementOffset;
	FRotator TurnOffset;
};
