// Fill out your copyright notice in the Description page of Project Settings.


#include "FlyingBridge.h"

// Sets default values
AFlyingBridge::AFlyingBridge()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	BridgeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bridge"));
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base"));
	PhysicsConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Physics Constraint"));
	Rope1 = CreateDefaultSubobject<UCableComponent>(TEXT("Rope1"));
	Rope2 = CreateDefaultSubobject<UCableComponent>(TEXT("Rope2"));
	Rope3 = CreateDefaultSubobject<UCableComponent>(TEXT("Rope3"));
	Rope4 = CreateDefaultSubobject<UCableComponent>(TEXT("Rope4"));
	BridgeMesh->SetupAttachment(RootComponent);
	BaseMesh->SetupAttachment(RootComponent);
	PhysicsConstraint->SetupAttachment(RootComponent);
	Rope1->SetupAttachment(RootComponent);
	Rope2->SetupAttachment(RootComponent);
	Rope3->SetupAttachment(RootComponent);
	Rope4->SetupAttachment(RootComponent);
	BridgeMesh->SetSimulatePhysics(true);
	bReplicates = true;
	RootComponent->SetIsReplicated(true);
	BridgeMesh->SetIsReplicated(true);
	PhysicsConstraint->SetIsReplicated(true);
	Rope1->SetIsReplicated(true);
	Rope2->SetIsReplicated(true);
	Rope3->SetIsReplicated(true);
	Rope4->SetIsReplicated(true);
}

// Called when the game starts or when spawned
void AFlyingBridge::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFlyingBridge::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

