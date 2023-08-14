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

void AShooterGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AShooterGameState, TeamOneScore);
	DOREPLIFETIME(AShooterGameState, TeamTwoScore);
}

void AShooterGameState::TeamOneScored(int Amount)
{
	if (HasAuthority())
	{
		TeamOneScore += Amount;
	}
}

void AShooterGameState::TeamTwoScored(int Amount)
{
	if (HasAuthority())
	{
		TeamTwoScore += Amount;
	}
}

void AShooterGameState::BeginPlay()
{
	Super::BeginPlay();
	TArray<AActor*> TempActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnLocation::StaticClass(), TempActors);
	for (AActor* SpawnLocation : TempActors)
	{
		SpawnLocations.Add(Cast<ASpawnLocation>(SpawnLocation));
	}
}

void AShooterGameState::PlayerScored(APlayerState* PlayerState)
{
	if (TeamOne.Contains(PlayerState))
	{
		TeamTwoScored(1);
	}
	else
	{
		TeamOneScored(1);
	}
}

void AShooterGameState::RestartPlayer(APlayerState* PlayerState)
{
	if(HasAuthority())
	{
		int TeamNumber = 0;
		if(TeamOne.Contains(PlayerState))
		{
			TeamNumber = 0;
		}
		else
		{
			TeamNumber = 1;
		}
		FVector RandomPoint = UKismetMathLibrary::RandomPointInBoundingBox(SpawnLocations[TeamNumber]->GetActorLocation(), SpawnLocations[TeamNumber]->SpawnBounds->GetScaledBoxExtent()); FTransform SpawnLocation = FTransform(SpawnLocations[TeamNumber]->GetActorRotation(), RandomPoint);
		GetWorld()->GetAuthGameMode()->RestartPlayerAtTransform(PlayerState->GetPlayerController(),SpawnLocation);
	}
}

void AShooterGameState::AddPlayerState(APlayerState* PlayerState)
{
	Super::AddPlayerState(PlayerState);
	if (Cast<AShooterPlayerState>(PlayerState))
	{
		AShooterPlayerState* NewShooterPlayerState = Cast<AShooterPlayerState>(PlayerState);
		if (TeamOne.Num() < TeamTwo.Num())
		{
			TeamOne.Add(NewShooterPlayerState);
		}
		else if (TeamTwo.Num() < TeamOne.Num())
		{
			TeamTwo.Add(NewShooterPlayerState);
		}
		else
		{
			if (rand() % 2 == 0)
			{
				TeamOne
					.Add(NewShooterPlayerState);
			}
			else
			{
				TeamTwo
					.Add(NewShooterPlayerState);
			}
		}
	}
}
