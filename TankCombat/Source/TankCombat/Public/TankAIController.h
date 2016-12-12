// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;
/**
 * 
 */
UCLASS()
class TANKCOMBAT_API ATankAIController : public AAIController
{
	GENERATED_BODY()
public:
	

private:	

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	//how close the AI tank can get to player before stopping
	float AcceptanceRadius = 3000.0f;
	
	
};
