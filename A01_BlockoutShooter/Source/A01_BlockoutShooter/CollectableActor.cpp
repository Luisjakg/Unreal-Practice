// Fill out your copyright notice in the Description page of Project Settings.


#include "CollectableActor.h"
#include "WeaponPlatform.h"
#include "A01_BlockoutShooterCharacter.h"

// Sets default values
ACollectableActor::ACollectableActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Hitbox = CreateDefaultSubobject<USphereComponent>(TEXT("Hitbox Component"));
	ItemComponent = CreateDefaultSubobject<UItemComponent>(TEXT("Item Component"));
	RootComponent = Hitbox;
	ItemComponent->SetupAttachment(RootComponent);

	bReplicates = true;
	Hitbox->SetIsReplicated(true);
	ItemComponent->SetIsReplicated(true);
}

void ACollectableActor::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                       UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep,
                                       const FHitResult& SweepResult)
{
	AA01_BlockoutShooterCharacter* Character = Cast
		<AA01_BlockoutShooterCharacter>(OtherActor);
	if (Character)
	{
		if (!Character->HeldWeapon)
		{
			Hitbox->OnComponentBeginOverlap.RemoveAll(this);
			ItemComponent->Attach(Character);

			if (Spawner)
			{
				Spawner->StartTimer();
				Spawner = nullptr;
			}
		}
	}
}

// Called when the game starts or when spawned
void ACollectableActor::BeginPlay()
{
	Super::BeginPlay();
	Hitbox->OnComponentBeginOverlap.AddDynamic(this, &ACollectableActor::OnBeginOverlap);
}

// Called every frame
void ACollectableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddActorLocalRotation(FRotator(0, 50 * DeltaTime,0));
}

void ACollectableActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	DOREPLIFETIME
	(ACollectableActor, Hitbox);
	DOREPLIFETIME
	(ACollectableActor, ItemComponent);

	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}
