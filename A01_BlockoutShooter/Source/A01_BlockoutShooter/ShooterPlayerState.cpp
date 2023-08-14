// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerState.h"

void AShooterPlayerState::ClientInitialize(AController* C)
{
	Super::ClientInitialize(C);
	if(HasAuthority())
    {
     GetWorld()->GetGameState()->AddPlayerState(this);
    }

}
