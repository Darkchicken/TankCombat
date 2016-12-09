// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"
// forward declaration
class UTankBarrel; 

// Holds Barrel's properties and Elevate method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANKCOMBAT_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void SetBarrelReference(UTankBarrel* BarrelToSet);

	// TODO add SetTurretReference

	void AimAt(FVector HitLocation, float LaunchSpeed);

private:

	void MoveBarrelTowards(FVector AimDirection);

	UTankBarrel* Barrel = nullptr;

		
	
};
