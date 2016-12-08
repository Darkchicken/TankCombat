// Fill out your copyright notice in the Description page of Project Settings.

#include "TankCombat.h"
#include "TankPlayerController.h"


void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
	//UE_LOG(LogTemp, Warning, TEXT("Player Controller ticking"));
}
void ATankPlayerController::BeginPlay() 
{
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Controller not posessing tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Controller posessing %s"), *(ControlledTank->GetName()));
	}
	
}


void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }

	FVector HitLocation; // OUT parameter
	if (GetSightRayHitLocation(HitLocation)) // has "side-effect", going to line trace
	{
		//UE_LOG(LogTemp, Warning, TEXT("LookDirection: %s"), *(HitLocation.ToString()));
		// TODO tell tank to aim at this point
	}
	
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	/// Find crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY); // Sets using OUT parameters
	auto ScreenLocation = FVector2D(ViewportSizeX*CrosshairXLocation, ViewportSizeY*CrosshairYLocation);
	UE_LOG(LogTemp, Warning, TEXT("ScreenLocation: %s"), *(ScreenLocation.ToString()))

	// "De-Project" the screen position of crosshair to world direction
	// Linetrace along the look direction and see what we hit (within max range)
	HitLocation = FVector(1.0);
	return true;
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}