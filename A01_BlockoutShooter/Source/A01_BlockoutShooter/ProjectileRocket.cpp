// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileRocket.h"

// Sets default values
AProjectileRocket::AProjectileRocket()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RocketMesh = CreateDefaultSubobject
    <UStaticMeshComponent>(TEXT
    ("Mesh"));
    RootComponent = RocketMesh;
    ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
    ProjectileMovementComponent -> SetUpdatedComponent(RocketMesh);

}

// Called when the game starts or when spawned
void AProjectileRocket::BeginPlay()
{
	Super::BeginPlay();

	ProjectileMovementComponent->InitialSpeed = 5000;
	ProjectileMovementComponent->MaxSpeed = 5000;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->ProjectileGravityScale = 0.5f;

	RocketMesh->SetSimulatePhysics(true);
	RocketMesh->SetCollisionProfileName("BlockAll");
	RocketMesh->SetNotifyRigidBodyCollision(true);
	RocketMesh->OnComponentHit.AddDynamic(this, &AProjectileRocket::OnRocketHit);
}

// Called every frame
void AProjectileRocket::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectileRocket::OnRocketHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, FVector Normal, const FHitResult& HitResult)
{
	if(OtherActor && Owner != OtherActor) {
     UE_LOG(LogTemp, Warning, TEXT("Rocket Exploded"));
     Destroy();
    }

}

void AProjectileRocket::FireInDirection(const FVector& ShootDirection)
{
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
	RocketMesh->AddImpulse(ShootDirection * ProjectileMovementComponent->InitialSpeed);
}

