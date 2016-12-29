// Fill out your copyright notice in the Description page of Project Settings.

#include "TankCombat.h"
#include "TankAimingComponent.h"
#include "Tank.h" 
#include "TankPlayerController.h"


void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
	
}
void ATankPlayerController::BeginPlay() 
{
	Super::BeginPlay();
	auto AimingComponent = GetPawn() ->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
	FoundAimingComponent(AimingComponent);
	
}

void ATankPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }

		//subscribe our local method to the tanks death event
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnPossessedTankDeath);

	}
}

void ATankPlayerController::OnPossessedTankDeath()
{
	StartSpectatingOnly();
}


void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetPawn()) { return; } // e.g. if not possessing
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }

	FVector HitLocation; // OUT parameter
	if (GetSightRayHitLocation(HitLocation)) // has "side-effect", going to line trace
	{
		//Tell controlled tank to aim at target
		AimingComponent->AimAt(HitLocation);
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
		return GetLookVectorHitLocation(LookDirection, HitLocation);
	}
	
	return false;
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
			ECollisionChannel::ECC_Camera
			))
	{
		//set hit location
		HitLocation = HitResult.Location;
		return true;
	}
	//return false if no hit
	return false;
}
