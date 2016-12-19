// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class TANKCOMBAT_API ATankAIController : public AAIController
{
	GENERATED_BODY()
public:

protected:
	//how close the AI tank can get to player before stopping
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float AcceptanceRadius = 8000.0f;

private:	

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	
	
	
};
