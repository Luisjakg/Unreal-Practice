#include "RotatingWorld.h"

// Sets default values
ARotatingWorld::ARotatingWorld()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Initialize rotation parameters
	TargetRotation = FRotator(0, 0, 0); // Set your desired initial rotation here
	RotationSpeed = 90.0f; // Set the rotation speed in degrees per second
	bIsRotating = false;
}

// Called when the game starts or when spawned
void ARotatingWorld::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ARotatingWorld::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// If we are currently rotating, update the rotation
	if (bIsRotating)
	{
		FRotator CurrentRotation = GetActorRotation();
		FRotator NewRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, DeltaTime, RotationSpeed);
		SetActorRotation(NewRotation);

		// Check if we reached the target rotation
		if (NewRotation.Equals(TargetRotation, 0.1f)) // Adjust the tolerance as needed
			{
			bIsRotating = false;
			}
	}
}

void ARotatingWorld::RotateWorld_Implementation(bool Horizontal)
{
	if (!bIsRotating)
	{
		// Calculate the target rotation based on the direction of rotation
		if (Horizontal)
		{
			TargetRotation.Yaw += 90.0f;
		}
		else
		{
			TargetRotation.Pitch += 90.0f;
		}

		// Set the flag to start rotating
		bIsRotating = true;
	}
}
