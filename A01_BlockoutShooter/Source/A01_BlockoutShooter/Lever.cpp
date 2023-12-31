// Fill out your copyright notice in the Description page of Project Settings.


#include "Lever.h"

// Sets default values
ALever::ALever()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	Arm = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Lever Arm"));
	Base = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Lever Base"));
	PhysicsConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Physics Constraint"));
	Arm->SetupAttachment(RootComponent);
	Base->SetupAttachment(RootComponent);
	PhysicsConstraint->SetupAttachment(RootComponent);
	Arm->SetSimulatePhysics(true);
	bReplicates = true;
	RootComponent->SetIsReplicated(true);
	Arm->SetIsReplicated(true);
	PhysicsConstraint->SetIsReplicated(true);

}

// Called when the game starts or when spawned
void ALever::BeginPlay()
{
	Super::BeginPlay();
	
}



// Called every frame
void ALever::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(HasAuthority())
	{

		if(Arm->GetRelativeRotation().Pitch >= 45)
		{
			if(WreckingBall)
			{
				WreckingBall->BallMesh->SetSimulatePhysics(true);
				WreckingBall->BallMesh->SetEnableGravity(true);
			}
		}
	}

}

