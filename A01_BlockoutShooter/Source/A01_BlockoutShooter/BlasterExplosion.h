// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/SphereComponent.h"
#include "Field/FieldSystemComponent.h"
#include "Net/UnrealNetwork.h"
#include "CoreMinimal.h"
#include "Field/FieldSystemActor.h"
#include "BlasterExplosion.generated.h"

/**
 * 
 */
UCLASS()
class A01_BLOCKOUTSHOOTER_API ABlasterExplosion : public AFieldSystemActor
{
	GENERATED_BODY()

public:
	ABlasterExplosion();
    UPROPERTY(EditAnywhere)
     USphereComponent* ExplosionRadius;
 
    UPROPERTY(EditAnywhere)
     UCullingField* CullingField;
 
    UPROPERTY(EditAnywhere)
     URadialVector* RadialVector;
 
    UPROPERTY(EditAnywhere)
     URadialFalloff* RadialFalloff;
 
    UPROPERTY(Replicated)
     float VelocityAmount;
 
    UPROPERTY(Replicated)
     float StrainAmount;

 void Explode();
 
 UFUNCTION(Server, Reliable)
 void ServerExplode();
 
 UFUNCTION(NetMulticast, Reliable)
 void MulticastExplode();
 
 void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

};
