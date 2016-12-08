// Fill out your copyright notice in the Description page of Project Settings.

#include "TankCombat.h"
#include "TankAIController.h"



void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Controller not posessing tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Controller posessing %s"), *(ControlledTank->GetName()));
	}

}


ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
