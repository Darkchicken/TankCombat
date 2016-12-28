// Copyright Josh Shucker 2016

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"


UCLASS()
class TANKCOMBAT_API ATank : public APawn
{
	GENERATED_BODY()

public :
	ATank();

	// Called by the engine when actor damage is dealt
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;

private:
	
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 InitalHealth = 100;

	UPROPERTY(VisibleAnywhere, Category = "Health")
	int32 CurrentHealth = InitalHealth;

};
