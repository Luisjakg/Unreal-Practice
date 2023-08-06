#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "A01_BlockoutShooterCharacter.h"
#include "ItemComponent.generated.h"

// Forward declaration of AA01_BlockoutShooterCharacter class

class AA01_BlockoutShooterCharacter;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class A01_BLOCKOUTSHOOTER_API UItemComponent : public USkeletalMeshComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties													
	AA01_BlockoutShooterCharacter* Character;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	UFUNCTION()
	virtual void Attach(AA01_BlockoutShooterCharacter* PickupCharacter);
	UFUNCTION()
	virtual void Detach();
	UFUNCTION()
	virtual void Use();
};
