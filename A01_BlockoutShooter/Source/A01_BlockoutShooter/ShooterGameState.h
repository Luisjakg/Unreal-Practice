// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "ShooterGameState.generated.h"

/**
 * 
 */
UCLASS()
class A01_BLOCKOUTSHOOTER_API AShooterGameState : public AGameStateBase
{
	GENERATED_BODY()
public:
	AShooterGameState();	
	
	UPROPERTY()
	int TeamOneScore;
	
    UPROPERTY()
    int TeamTwoScore;
	
    void TeamOneScored(int Amount);
	
    void TeamTwoScored(int Amount);
};
