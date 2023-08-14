	// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "GameFramework/GameStateBase.h"
#include "ShooterPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class A01_BLOCKOUTSHOOTER_API AShooterPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	virtual void ClientInitialize(AController* C) override;
	
};
