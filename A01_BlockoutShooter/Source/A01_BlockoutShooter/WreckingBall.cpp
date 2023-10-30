// Fill out your copyright notice in the Description page of Project Settings.


#include "WreckingBall.h"

// Sets default values
AWreckingBall::AWreckingBall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	TopMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Top"));
	BallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ball"));
	PhysicsConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Physics Constraint"));
	Rope = CreateDefaultSubobject<UCableComponent>(TEXT("Rope"));
	TopMesh->SetupAttachment(RootComponent);
	BallMesh->SetupAttachment(RootComponent);
	PhysicsConstraint->SetupAttachment(RootComponent);
	Rope->SetupAttachment(RootComponent);
	BallMesh->SetSimulatePhysics(false);
	BallMesh->SetEnableGravity(false);
	bReplicates = true;
	RootComponent->SetIsReplicated(true);
	BallMesh->SetIsReplicated(true);
	PhysicsConstraint->SetIsReplicated(true);
	Rope->SetIsReplicated(true);
}

// Called when the game starts or when spawned
void AWreckingBall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWreckingBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

