// Copyright Josh Shucker 2016

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class AProjectile;


UCLASS()
class TANKCOMBAT_API ATank : public APawn
{
	GENERATED_BODY()
public:
	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();


private:
	// Sets default values for this pawn's properties
	ATank();

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;

	// TODO remove once copied
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 4000.0f; // sensible default

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTimeInSeconds = 3.0f;

	UTankBarrel* Barrel = nullptr; // TODO remove

	double LastFireTime = 0;
	
	
};
