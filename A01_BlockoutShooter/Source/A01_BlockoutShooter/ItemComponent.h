#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "ItemComponent.generated.h"

// Forward declaration of ABlockoutShooterCharacter class
class AA01_BlockoutShooterCharacter;

UCLASS()
class AA01_BLOCKOUTSHOOTER_API UItemComponent : public USkeletalMeshComponent
{
	GENERATED_BODY()

public:
	AA01_BlockoutShooterCharacter* Character;

	UFUNCTION()
	virtual void Attach(AA01_BlockoutShooterCharacter* PickupCharacter);
	UFUNCTION()
	virtual void Detach();
	UFUNCTION()
	virtual void Use();
};
