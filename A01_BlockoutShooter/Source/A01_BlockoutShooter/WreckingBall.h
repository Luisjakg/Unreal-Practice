// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CableComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WreckingBall.generated.h"

UCLASS()
class A01_BLOCKOUTSHOOTER_API AWreckingBall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWreckingBall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* TopMesh;
	UPROPERTY(EditAnywhere)	
	UStaticMeshComponent* BallMesh;
	UPROPERTY(EditAnywhere)
	UPhysicsConstraintComponent* PhysicsConstraint;
	UPROPERTY(EditAnywhere)
	UCableComponent* Rope;

};
