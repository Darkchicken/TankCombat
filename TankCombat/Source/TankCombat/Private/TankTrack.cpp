// Fill out your copyright notice in the Description page of Project Settings.

#include "TankCombat.h"
#include "TankTrack.h"


void UTankTrack::SetThrottle(float Throttle)
{
	//auto Time = GetWorld()->GetTimeSeconds();
	auto Name = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s throttle: %f"), *Name,Throttle);

	// TODO clamp actual throttle value between -1 and 1
}

