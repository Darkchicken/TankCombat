// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" //must be the last include

class ATank;
class UTankAimingComponent;
/**
 * Responisble for helping the player aim
 */
UCLASS()
class TANKCOMBAT_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintCallable, Category = "Setup")
	ATank* GetControlledTank() const;

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* AimingCompRef);


private:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	// start tank moving barrel so a shot will hit where crosshair intersects world
	void AimTowardsCrosshair();

	// return an OUT parameter, true if hit landscape
	bool GetSightRayHitLocation(FVector& HitLocation) const;

	// Get the direction that the player is looking
	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;

	// Get the location that the LineTrace hits
	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;

	UPROPERTY(EditDefaultsOnly)
	float CrosshairXLocation = 0.5f;
	UPROPERTY(EditDefaultsOnly)
	float CrosshairYLocation = 0.33333f;

	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange = 1000000.0f;
	
};
