#include "RotatingWorld.h"

// Sets default values
ARotatingWorld::ARotatingWorld()
{
    // Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    // Initialize rotation parameters
    TargetRotation = FRotator(0, 0, 0); // Set your desired initial rotation here
    RotationSpeed = 2.0f; // Set the rotation speed in degrees per second
    bIsRotating = false;

    // Enable replication for this actor
    bReplicates = true;

    // // Set replication for attached UStaticMeshComponents
    // TArray<UStaticMeshComponent*> AttachedStaticMeshComponents;
    // GetComponents<UStaticMeshComponent>(AttachedStaticMeshComponents);
    //
    // for (UStaticMeshComponent* AttachedStaticMesh : AttachedStaticMeshComponents)
    // {
    //     AttachedStaticMesh->SetIsReplicated(true);
    // }
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

void ARotatingWorld::LaunchPlayersIntoAir_Implementation()
{
    // for (AA01_BlockoutShooterCharacter* Controller : TActorRange<AA01_BlockoutShooterCharacter>(GetWorld()))
    // {
    //     // Get the controlled character
    //     
    //         // Calculate the launch direction (upward)
    //         FVector LaunchDirection = FVector(0.0f, 0.0f, 1.0f); // Upward direction
    //         float LaunchStrength = 1500.0f; // Adjust this value as needed
    //
    //         // Launch the character into the air
    //         Controller->LaunchCharacter(LaunchDirection * LaunchStrength, false, false);
    //     
    // }
}

void ARotatingWorld::OnRep_TargetRotation()
{
    SetActorRotation(TargetRotation);
}

void ARotatingWorld::RotateWorld(FRotator Rotation)
{
    if (HasAuthority())
    {
        MulticastRotate(Rotation);
    }
}

void ARotatingWorld::MulticastRotate_Implementation(FRotator Rotation)
{
    if (bIsRotating) return;
    LaunchPlayersIntoAir();
    TargetRotation += Rotation;
    bIsRotating = true;
}
// { OLD CODE
//     if (!bIsRotating)
//     {
//         LaunchPlayersIntoAir();
//         if (Horizontal)
//         {
//             TargetRotation.Yaw += Amount;
//         }
//         else
//         {
//             TargetRotation.Pitch += Amount;
//         }
//
//         bIsRotating = true;
//     }
// }

void ARotatingWorld::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    // Add any replicated properties here, for example:
    // DOREPLIFETIME(ARotatingWorld, TargetRotation);
}
