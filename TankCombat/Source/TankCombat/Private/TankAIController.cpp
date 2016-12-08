// Fill out your copyright notice in the Description page of Project Settings.

#include "TankCombat.h"
#include "TankAIController.h"



void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	auto PlayerTank = GetPlayerTank();
	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Controller cant find Player tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Controller found Player: %s"), *(PlayerTank->GetName()));
	}

}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetPlayerTank())
	{
		// TODO move towards player

		// Aim Towards Player
		GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());

		// TODO Fire if ready
	}
	//UE_LOG(LogTemp, Warning, TEXT("Player Controller ticking"));
}


ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn) { return nullptr; }
	return Cast<ATank>(PlayerPawn);
}
