// Fill out your copyright notice in the Description page of Project Settings.

#include "TankCombat.h"
#include "TankAimingComponent.h"
#include "TankAIController.h"



void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();
	if (!ensure(PlayerTank && ControlledTank)) { return; }
	
	// move towards player
	MoveToActor(PlayerTank, AcceptanceRadius);

	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	// Aim Towards Player
	AimingComponent->AimAt(PlayerTank->GetActorLocation());

	// TODO Fix firing
	// Fire if ready
	//AimingComponent->Fire();
	
	
}



