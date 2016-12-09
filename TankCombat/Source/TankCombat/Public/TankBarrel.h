// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent), hidecategories = ("Collision"))
class TANKCOMBAT_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
public:
	//-1 is max downward movement, +1 is max upward movement
	void Elevate(float RelativeSpeed);

private:
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxDegreesPerSecond = 20.0f; // sensible default

	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxElevationDegrees = 40.0f; // sensible default

	UPROPERTY(EditAnywhere, Category = Setup)
	float MinElevationDegrees = 0.0f; // sensible default
	
	
	
	
};
