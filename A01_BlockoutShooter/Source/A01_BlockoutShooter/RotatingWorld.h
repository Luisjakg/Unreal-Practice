// RotatingWorld.h

#pragma once

#include "EngineUtils.h"
#include "Net/UnrealNetwork.h"
#include "A01_BlockoutShooterCharacter.h"

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
	
	UFUNCTION()
	void OnRep_TargetRotation();

	void RotateWorld(FRotator Rotation);

	// Replicated variables
	UPROPERTY()
	FRotator TargetRotation;

	UFUNCTION(NetMulticast, Reliable)
	void MulticastRotate(FRotator Rotation);

private:
	float RotationSpeed;
	bool bIsRotating;
	float MinTime;
	float Timer;
};
