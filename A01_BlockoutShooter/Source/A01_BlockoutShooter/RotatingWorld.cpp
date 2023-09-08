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

    MinTime = 4.5f; // We use a min Timer to force the rotation in case it takes longer than usual
    Timer = 0;
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
        Timer += DeltaTime;

        if (Timer > MinTime)
        {
            bIsRotating = false;
            SetActorRotation(TargetRotation);
            Timer = 0;
            return;
        }
        
        // Check if we reached the target rotation
        if (NewRotation.Equals(TargetRotation, 0.1f))
        {
            bIsRotating = false;
        }
    }
}

void ARotatingWorld::OnRep_TargetRotation()
{
    SetActorRotation(TargetRotation);
}

void ARotatingWorld::RotateWorld(FRotator Rotation)
{
    if (HasAuthority())
    {
        if (bIsRotating) return;
        MulticastRotate(Rotation);
    }
}

void ARotatingWorld::MulticastRotate_Implementation(FRotator Rotation)
{
    if (bIsRotating) return;

    // Ensure the new rotation doesn't exceed 360 degrees
    TargetRotation += Rotation;
    TargetRotation.Normalize();

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

// void ARotatingWorld::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
// {
//     Super::GetLifetimeReplicatedProps(OutLifetimeProps);
//     // Add any replicated properties here, for example:
//     // DOREPLIFETIME(ARotatingWorld, TargetRotation);
// }
