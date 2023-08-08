// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Net/UnrealNetwork.h"
#include "ProjectileRocket.generated.h"

UCLASS()
class A01_BLOCKOUTSHOOTER_API AProjectileRocket : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectileRocket();

	UPROPERTY(EditAnywhere)
    UNiagaraSystem* NS_Explosion;

	UPROPERTY(EditAnywhere)
	float Damage = 20;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// The Rocket Mesh
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", Replicated)
	UStaticMeshComponent* RocketMesh;

	// The Projectile Movement Component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", Replicated)
	UProjectileMovementComponent* ProjectileMovementComponent;

	// Reference to the owner class
	AActor* Owner;

	// Function called when the Rocket hits an object and explodes
	UFUNCTION()
	void OnRocketHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector Normal, const FHitResult& HitResult);

	// Function that will start firing the rocket in a provided direction
	void FireInDirection(const FVector& ShootDirection);

	UFUNCTION(Server, Reliable)
	void ServerExplode(AActor* OtherActor, const FHitResult& HitResult);
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
