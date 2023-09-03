// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CableComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FlyingBridge.generated.h"

UCLASS()
class A01_BLOCKOUTSHOOTER_API AFlyingBridge : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFlyingBridge();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* BridgeMesh;
	
	UPROPERTY(EditAnywhere)	
	UStaticMeshComponent* BaseMesh;
	
	UPROPERTY(EditAnywhere)
	UPhysicsConstraintComponent* PhysicsConstraint;
	
	UPROPERTY(EditAnywhere)
	UCableComponent* Rope1;

	UPROPERTY(EditAnywhere)
	UCableComponent* Rope2;

	UPROPERTY(EditAnywhere)
	UCableComponent* Rope3;

	UPROPERTY(EditAnywhere)
	UCableComponent* Rope4;
};
