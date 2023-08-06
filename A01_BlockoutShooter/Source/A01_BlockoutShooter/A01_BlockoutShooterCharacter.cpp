// Fill out your copyright notice in the Description page of Project Settings.


#include "A01_BlockoutShooterCharacter.h"

// Sets default values
AA01_BlockoutShooterCharacter::AA01_BlockoutShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AA01_BlockoutShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AA01_BlockoutShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AA01_BlockoutShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

