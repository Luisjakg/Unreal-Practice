#include "WeaponPlatform.h"

// Sets default values
AWeaponPlatform::AWeaponPlatform()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	SpawnerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SpawnerMesh->SetupAttachment(RootComponent);
	
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AWeaponPlatform::BeginPlay()
{
	Super::BeginPlay();
	StartTimer();
}

// Called every frame
void AWeaponPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWeaponPlatform::StartTimer()
{
	GetWorld()->GetTimerManager().SetTimer(SpawnWeaponTimerHandle, this, &AWeaponPlatform::SpawnWeapon, 5);
}

void AWeaponPlatform::SpawnWeapon()
{
	if (HasAuthority())
	{
		ServerSpawnWeapon();
	}
}

void AWeaponPlatform::ServerSpawnWeapon_Implementation()
{
	int RandWeaponIndex = FMath::RandRange(0, WeaponClasses.Num() - 1);
	FVector SpawnLocation = GetActorLocation() + GetActorUpVector() * 50;
	ACollectableActor* SpawnedWeapon = Cast<ACollectableActor>(GetWorld()->SpawnActor(WeaponClasses[RandWeaponIndex], &SpawnLocation));

	if (SpawnedWeapon)
	{
		// Attach the spawned weapon to the RootComponent of this actor
		SpawnedWeapon->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
		
		// SpawnedWeapon->SetActorRelativeLocation(FVector::ZeroVector);
		// SpawnedWeapon->SetActorRelativeRotation(FRotator::ZeroRotator);

		SpawnedWeapon->Spawner = this;
	}
}



