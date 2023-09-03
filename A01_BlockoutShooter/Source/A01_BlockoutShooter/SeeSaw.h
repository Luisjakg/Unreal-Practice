// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "RotatingWorld.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SeeSaw.generated.h"

UCLASS()
class A01_BLOCKOUTSHOOTER_API ASeeSaw : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASeeSaw();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* PlatformMesh;
	UPROPERTY(EditAnywhere)	
	UStaticMeshComponent* BaseMesh;
	UPROPERTY(EditAnywhere)
	UPhysicsConstraintComponent* PhysicsConstraint;

	UPROPERTY(EditAnywhere)
	ARotatingWorld* RotatingWorld;

private:
	bool IsRotating;

};
