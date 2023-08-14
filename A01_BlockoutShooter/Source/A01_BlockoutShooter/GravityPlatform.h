// GravityPlatform.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Net/UnrealNetwork.h"
#include "GravityPlatform.generated.h"

UCLASS()
class A01_BLOCKOUTSHOOTER_API AGravityPlatform : public AActor
{
	GENERATED_BODY()

public:
	AGravityPlatform();

	UPROPERTY(EditAnywhere, Replicated)
	UBoxComponent* Hitbox;
	
	UPROPERTY(EditAnywhere, Category = "Gravity")
	FVector GravityDirection;

	UFUNCTION()
	void OnBeginOverlap
	(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComponent,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
