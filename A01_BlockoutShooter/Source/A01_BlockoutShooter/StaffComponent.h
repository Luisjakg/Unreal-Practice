// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "A01_BlockoutShooterCharacter.h"
#include "Camera/CameraComponent.h"
#include "CoreMinimal.h"
#include "ItemComponent.h"
#include "StaffComponent.generated.h"

/**
 * 
 */
UCLASS()
class A01_BLOCKOUTSHOOTER_API UStaffComponent : public UItemComponent
{
	GENERATED_BODY()


public:
	virtual void Use() override;
    virtual void Detach() override;
    virtual void Attach(AA01_BlockoutShooterCharacter* PickupCharacter) override;
	
    UFUNCTION(Server, Reliable)
	void ServerBlaster();
	
    UFUNCTION(NetMulticast, Reliable)
	void MulticastBlaster(FVector ParticleVelocity);
 
    UPROPERTY(EditAnywhere)
    UNiagaraSystem* NS_Blaster;

};
