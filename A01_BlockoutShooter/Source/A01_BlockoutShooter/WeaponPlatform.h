// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CollectableActor.h"
#include "WeaponPlatform.generated.h"

UCLASS()
class A01_BLOCKOUTSHOOTER_API AWeaponPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponPlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* SpawnerMesh;
	
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<ACollectableActor>> WeaponClasses;
	
	FTimerHandle SpawnWeaponTimerHandle;
	
	void StartTimer();
	
	UFUNCTION()
	void SpawnWeapon();
	
	UFUNCTION(Server, Reliable)
	void ServerSpawnWeapon();

};
