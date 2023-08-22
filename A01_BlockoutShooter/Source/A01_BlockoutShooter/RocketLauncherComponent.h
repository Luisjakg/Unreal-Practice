#pragma once

#include "CoreMinimal.h"
#include "ItemComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Net/UnrealNetwork.h"
#include "Camera/CameraComponent.h"
#include "RocketLauncherComponent.generated.h"

class AProjectileRocket;
class UInputAction;
class UInputMappingContext;

/**
 * 
 */
UCLASS()
class A01_BLOCKOUTSHOOTER_API URocketLauncherComponent : public UItemComponent
{
	GENERATED_BODY()

public:
	// Constructor
	URocketLauncherComponent();

	// Properties
	UPROPERTY(EditAnywhere)
	FVector BarrelOffset;

	UPROPERTY(EditAnywhere)
	UInputMappingContext* WeaponMappingContext;

	UPROPERTY(EditAnywhere)
	UInputAction* PrimaryFireAction;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AProjectileRocket> RocketClass;

	// Functions
	virtual void Attach(AA01_BlockoutShooterCharacter* AttachCharacter) override;
	virtual void Detach() override;
	virtual void Use() override;
	
	UFUNCTION(Server, Reliable)
     void ServerSpawnRocket();

	UPROPERTY(EditAnywhere)
	UNiagaraSystem* NS_ShootParticle;

	UFUNCTION(NetMulticast, Reliable)
	void MulticastShootParticle(FVector Location, FRotator Rotation);
};
