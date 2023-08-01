#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "ProjectileRocket.generated.h"

UCLASS()
class A01_BLOCKOUTSHOOTER_API AProjectileRocket : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AProjectileRocket();

	// The Projectile Movement Component
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	UStaticMeshComponent* RocketMesh;

	// Other required Actor Component property (you can replace "UActorComponent" with the actual type of your component)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	UProjectileMovementComponent* ProjectileMovementComponent;

	AActor* Owner;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnRocketHit
	(UPrimitiveComponent* HitComponent, AActor*OtherActor,
		UPrimitiveComponent* OtherComponent, FVector Normal,const FHitResult& HitResult);

	void FireInDirection(const FVector& ShootDirection);
};
