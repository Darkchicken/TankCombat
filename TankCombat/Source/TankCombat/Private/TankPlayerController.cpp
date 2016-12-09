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
		//Tell controlled tank to aim at target
		GetControlledTank()->AimAt(HitLocation);
	}
	
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	/// Find crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY); // Sets using OUT parameters
	auto ScreenLocation = FVector2D(ViewportSizeX*CrosshairXLocation, ViewportSizeY*CrosshairYLocation);
	
	FVector LookDirection;
	if (GetLookDirection( ScreenLocation, LookDirection))
	{
		
		// Linetrace along the look direction and see what we hit (within max range)
		if (GetLookVectorHitLocation(LookDirection, HitLocation))
		{
			
			//UE_LOG(LogTemp, Warning, TEXT("Hit Location: %s"), *(HitLocation.ToString()));
		}
	}
	
	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	/// "De-Project" the screen position of crosshair to world direction
	FVector CameraWorldLocation;
	
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X, 
		ScreenLocation.Y, 
		CameraWorldLocation, 
		LookDirection);
		
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection*LineTraceRange);
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetPawn());
	if (GetWorld()->LineTraceSingleByChannel(
			HitResult,
			StartLocation,
			EndLocation,
			ECollisionChannel::ECC_Visibility
			))
	{
		//set hit location
		HitLocation = HitResult.Location;
		return true;
	}
	//return false if no hit
	return false;
}
ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}