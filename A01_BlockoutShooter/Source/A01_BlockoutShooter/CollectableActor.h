#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemComponent.h"
#include "Components/SphereComponent.h"
#include "CollectableActor.generated.h"

class AWeaponPlatform;

UCLASS()
class A01_BLOCKOUTSHOOTER_API ACollectableActor : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ACollectableActor();

	UPROPERTY(EditAnywhere, Replicated) // Adding Replicated to enable network replication
	USphereComponent* Hitbox;
	
	UPROPERTY(EditAnywhere, Replicated) // Adding Replicated to enable network replication
	UItemComponent* ItemComponent;

	UFUNCTION()
	void OnBeginOverlap
	(UPrimitiveComponent* OverlappedComponent,
	 AActor* OtherActor, UPrimitiveComponent* OtherComponent,
	 int32 OtherBodyIndex, bool bFromSweep,
	 const FHitResult& SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	AWeaponPlatform* Spawner;
};
