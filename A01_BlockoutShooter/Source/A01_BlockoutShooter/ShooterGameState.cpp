// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterGameState.h"

#include "SpawnLocation.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

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

void AShooterGameState::BeginPlay()
{
	Super::BeginPlay();
	TArray<AActor*> TempActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnLocation::StaticClass(), TempActors);
	for(AActor* SpawnLocation : TempActors)
	{
		SpawnLocations.Add(Cast<ASpawnLocation>(SpawnLocation));
	}
}

void AShooterGameState::RestartPlayer()
{
	FVector RandomPoint = UKismetMathLibrary::RandomPointInBoundingBox(SpawnLocations[0]->GetActorLocation(), SpawnLocations[0]->SpawnBounds->GetScaledBoxExtent());
	FTransform SpawnLocation = FTransform(SpawnLocations[0]->GetActorRotation(), RandomPoint);
	GetWorld()->GetAuthGameMode()->RestartPlayerAtTransform(GetWorld()->GetGameState()->PlayerArray[0]->GetPlayerController(),SpawnLocation);
}
