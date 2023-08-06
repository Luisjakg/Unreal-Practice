// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterGameState.h"

AShooterGameState::AShooterGameState()
{
	TeamOneScore = 0;
	TeamTwoScore = 0;
}

void AShooterGameState::TeamOneScored(int Amount)
{
	TeamOneScore += Amount;
}

void AShooterGameState::TeamTwoScored(int Amount)
{
	TeamTwoScore += Amount;
}
