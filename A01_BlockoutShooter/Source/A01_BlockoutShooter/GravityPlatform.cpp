// GravityPlatform.cpp

#include "GravityPlatform.h"
#include "A01_BlockoutShooterCharacter.h"

AGravityPlatform::AGravityPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	Hitbox = CreateDefaultSubobject<UBoxComponent>(TEXT("Hitbox"));
	RootComponent = Hitbox;

	Hitbox->OnComponentBeginOverlap.AddDynamic(this, &AGravityPlatform::OnBeginOverlap);
	GravityDirection = FVector(0.0f, 0.0f, -1.0f);

	SpawnerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SpawnerMesh->SetupAttachment(RootComponent);
}

void AGravityPlatform::BeginPlay()
{
	Super::BeginPlay();
	// Hitbox->OnComponentBeginOverlap.AddDynamic(this, &AGravityPlatform::OnBeginOverlap);
}

void AGravityPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGravityPlatform::OnBeginOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComponent,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult
)
{
	UE_LOG(LogTemp, Warning, TEXT("AGravityPlatform::OnBeginOverlap()"));
	AA01_BlockoutShooterCharacter* Character = Cast<AA01_BlockoutShooterCharacter>(OtherActor);
	if (Character)
	{
		// Set the new gravity direction
		// Character->SetGravityDirection(GravityDirection);

		// Launch the character upwards with a specified force to make transition smoother
		FVector LaunchForce = FVector(0.0f, 0.0f, 1000.0f); // Adjust the force as needed
		Character->LaunchCharacter(LaunchForce, true, true);
	}
}

void AGravityPlatform::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}
