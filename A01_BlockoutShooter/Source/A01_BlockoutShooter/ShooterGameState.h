// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "SpawnLocation.h"
#include "Net/UnrealNetwork.h"
#include "ShooterPlayerState.h"
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
	
	UPROPERTY(Replicated)
	int TeamOneScore;
	
    UPROPERTY(Replicated)
    int TeamTwoScore;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
    void TeamOneScored(int Amount);
	
    void TeamTwoScored(int Amount);

	virtual void BeginPlay() override;
	
	void PlayerScored(APlayerState* PlayerState);
	void RestartPlayer(APlayerState* PlayerState);
	
    TArray<ASpawnLocation*> SpawnLocations;

	UPROPERTY(EditAnywhere)
     TArray<AShooterPlayerState*> TeamOne;
	
    UPROPERTY(EditAnywhere)
	TArray<AShooterPlayerState*> TeamTwo;
	
    virtual void AddPlayerState(APlayerState* PlayerState) override;

};
