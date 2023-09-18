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

	bIsRotating = false;
	bActive = false;
}

// Called when the game starts or when spawned
void ASeeSaw::BeginPlay()
{
	Super::BeginPlay();
	
	// Store the initial rotation of the SeeSaw
	AdditionalRotation = FRotator(0, 0, 0);
	
}

// Called every frame
void ASeeSaw::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!RotatingWorld) return;
	if (!bActive)
	{
		// Check if rotation is close to 0,0,0
		if (FMath::IsNearlyZero(PlatformMesh->GetRelativeRotation().Pitch, 0.1f) && FMath::IsNearlyZero(PlatformMesh->GetRelativeRotation().Roll, 0.1f))
		{
			bActive = true;
		}
		else return;
	}

	if (HasAuthority())
	{
		
		
		if (PlatformMesh->GetRelativeRotation().Pitch - AdditionalRotation.Pitch >= 15 && !bIsRotating)
		{
			//Log to see relative rotation pitch
			UE_LOG(LogTemp, Warning, TEXT("Pitch: %f"), PlatformMesh->GetRelativeRotation().Pitch);
			bIsRotating = true;
			RotatingWorld->RotateWorld(FRotator(90, 0, 0));
			bActive = false;
		}
		else if (PlatformMesh->GetRelativeRotation().Pitch - AdditionalRotation.Pitch <= -15 && !bIsRotating)
		{
			bIsRotating = true;
			RotatingWorld->RotateWorld(FRotator(-90, 0, 0));
			
			bActive = false;
		}
		else if (PlatformMesh->GetRelativeRotation().Roll - AdditionalRotation.Roll >= 15 && !bIsRotating)
		{
			bIsRotating = true;
			RotatingWorld->RotateWorld(FRotator(0, 0, 90));
			
			bActive = false;
		}
		else if (PlatformMesh->GetRelativeRotation().Roll - AdditionalRotation.Roll <= -15 && !bIsRotating)
		{
			bIsRotating = true;
			RotatingWorld->RotateWorld(FRotator(0, 0, -90));
			
			bActive = false;
		}
		else if (BaseMesh->GetRelativeRotation().Pitch - AdditionalRotation.Pitch  == 0 && bIsRotating)
		{
			UE_LOG(LogTemp, Warning, TEXT("READY!"));
			bIsRotating = false;
			// RotatingWorld->RotateWorld(true);
		}
	}
}
