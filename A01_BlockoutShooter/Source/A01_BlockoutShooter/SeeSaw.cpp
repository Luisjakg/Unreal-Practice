// Fill out your copyright notice in the Description page of Project Settings.


#include "SeeSaw.h"

// Sets default values
ASeeSaw::ASeeSaw()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Platform"));
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base"));
	PhysicsConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Physics Constraint"));
	PlatformMesh->SetupAttachment(RootComponent);
	BaseMesh->SetupAttachment(RootComponent);
	PhysicsConstraint->SetupAttachment(RootComponent);
	
	PlatformMesh->SetSimulatePhysics(true);
	bReplicates = true;
	RootComponent->SetIsReplicated(true);
	PlatformMesh->SetIsReplicated(true);
	PhysicsConstraint->SetIsReplicated(true);

	IsRotating = false;
}

// Called when the game starts or when spawned
void ASeeSaw::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASeeSaw::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority())
	{
		if (PlatformMesh->GetRelativeRotation().Pitch >= 15 && !IsRotating)
		{
			IsRotating = true;
			RotatingWorld->RotateWorld(true, 90);
		}
		else if (PlatformMesh->GetRelativeRotation().Pitch <= -15 && !IsRotating)
		{
			IsRotating = true;
			RotatingWorld->RotateWorld(true, -90);
		}
		// else if (PlatformMesh->GetRelativeRotation().Yaw  ==  && !IsRotating)
		// {
		// 	
		// }
		else if (BaseMesh->GetRelativeRotation().Pitch  == 0 && IsRotating)
		{
			UE_LOG(LogTemp, Warning, TEXT("READY!"));
			IsRotating = false;
			// RotatingWorld->RotateWorld(true);
		}
	}

}

