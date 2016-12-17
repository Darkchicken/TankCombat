// Fill out your copyright notice in the Description page of Project Settings.

#include "TankCombat.h"
#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;	
}

void UTankTrack::BeginPlay()
{
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

// Called every frame tracks are in contact
void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("IM HIT!!!"));
	//Drive the tracks
	DriveTrack();
	//apply a sideways force
	ApplySidewaysForce();
	// reset throttle
	CurrentThrottle = 0.0f;
}


void UTankTrack::ApplySidewaysForce()
{
	// Calculate slippage speed (1 if totally sideways, 0 if no sideways velocity)
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	// Work out required acceleration this frame to correct (apply acceleration in opposite direction to slippage)
	auto DeltaTime = GetWorld()->GetDeltaSeconds();
	auto CorrectionAcceleration = SlippageSpeed / DeltaTime * -GetRightVector();
	// Calculate applied sideways force
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2; // 2 tracks
	TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::SetThrottle(float Throttle)
{
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle+Throttle, -1, 1);
}
void UTankTrack::DriveTrack()
{
	auto ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}



