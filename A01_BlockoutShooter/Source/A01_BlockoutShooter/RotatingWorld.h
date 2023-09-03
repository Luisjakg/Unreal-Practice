// RotatingWorld.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Net/UnrealNetwork.h" // Include this for replication
#include "A01_BlockoutShooterCharacter.h"
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

	void RotateWorld(bool Horizontal, int Amount);

	UFUNCTION(Server, Reliable)
	void LaunchPlayersIntoAir();

	// Replicated variables
	UPROPERTY(ReplicatedUsing = OnRep_TargetRotation)
	FRotator TargetRotation;

	UFUNCTION(NetMulticast, Reliable)
	void MulticastRotate(bool Horizontal, int Amount);

private:
	float RotationSpeed;
	bool bIsRotating;
};
