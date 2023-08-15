// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectileRocket.h"
#include "A01_BlockoutShooterCharacter.h"


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
	
	bReplicates = true;
	RocketMesh->SetIsReplicated(true);
	ProjectileMovementComponent->SetIsReplicated(true);
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
	if(HasAuthority())
	{
		if(OtherActor && Owner != OtherActor)
		{
			ServerExplode(OtherActor, HitResult);
		}
	}
}

void AProjectileRocket::FireInDirection(const FVector& ShootDirection)
{
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
	RocketMesh->AddImpulse(ShootDirection * ProjectileMovementComponent->InitialSpeed);
}

void AProjectileRocket::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AProjectileRocket, RocketMesh);
    DOREPLIFETIME(AProjectileRocket, ProjectileMovementComponent);
}

void AProjectileRocket::MulticastExplode_Implementation()
{
	if(NS_Explosion)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), NS_Explosion, this->GetActorLocation(), this->GetActorRotation());
	}
}

void AProjectileRocket::ServerExplode_Implementation(AActor* OtherActor, const FHitResult& HitResult)
{
	if(OtherActor && Owner != OtherActor) {
		//UE_LOG(LogTemp, Warning, TEXT("Rocket Exploded"));
		MulticastExplode();
		TArray<FHitResult> HitResults;
		FCollisionShape CollisionSphere = FCollisionShape::MakeSphere(500);
		GetWorld()->SweepMultiByChannel(HitResults, HitResult.Location, HitResult.Location, FQuat::Identity, ECC_Pawn, CollisionSphere);

		if(HitResults.Num() > 0)
		{
			for(FHitResult Hit : HitResults)
			{
				AA01_BlockoutShooterCharacter* HitCharacter = Cast<AA01_BlockoutShooterCharacter>(Hit.GetActor());
				if(HitCharacter)
				{
					HitCharacter->DealDamage(Damage);
				}
			}
		}
		Destroy();
	}
}

