// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineUtils.h"
#include "A01_BlockoutShooterCharacter.h"
#include "CoreMinimal.h"
#include "ItemComponent.h"
#include "PowItemComponent.generated.h"

/**
 * 
 */
UCLASS()
class A01_BLOCKOUTSHOOTER_API UPowItemComponent : public UItemComponent
{
	GENERATED_BODY()

public:
	virtual void Use() override;
	virtual void Detach() override;
	virtual void Attach(AA01_BlockoutShooterCharacter* PickupCharacter) override;
	UFUNCTION(Server, Reliable)
	void ServerPow();

};