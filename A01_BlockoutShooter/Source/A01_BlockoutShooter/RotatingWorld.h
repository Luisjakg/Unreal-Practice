// RotatingWorld.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RotatingWorld.generated.h"

UCLASS()
class A01_BLOCKOUTSHOOTER_API ARotatingWorld : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARotatingWorld();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Rotate the world either horizontally or vertically
	UFUNCTION(NetMulticast, Reliable)
	void RotateWorld(bool Horizontal);

private:
	FRotator TargetRotation;
	float RotationSpeed;
	bool bIsRotating;
};
