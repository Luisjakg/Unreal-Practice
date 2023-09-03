// Fill out your copyright notice in the Description page of Project Settings.


#include "PowItemComponent.h"


void UPowItemComponent::Use()
{
	Super::Use();
	ServerPow();
}

void UPowItemComponent::Detach()
{
	Super::Detach();
}

void UPowItemComponent::Attach(AA01_BlockoutShooterCharacter* PickupCharacter)
{
	Super::Attach(PickupCharacter);
	if(!PickupCharacter)
	{
		return;
	}
	Character = PickupCharacter;
	Character->HeldWeapon = this;
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	AttachToComponent(Character->GetMesh(), AttachmentRules, FName("GunPoint"));
	Super::Attach(PickupCharacter);
}

void UPowItemComponent::ServerPow_Implementation()
{
	for (AA01_BlockoutShooterCharacter* Controller : TActorRange<AA01_BlockoutShooterCharacter>(GetWorld()))
	{
	    // Get the controlled character
	    
	        // Calculate the launch direction (upward)
	        FVector LaunchDirection = FVector(0.0f, 0.0f, 1.0f); // Upward direction
	        float LaunchStrength = 1500.0f; // Adjust this value as needed
	
	        // Launch the character into the air
	        Controller->LaunchCharacter(LaunchDirection * LaunchStrength, false, false);
			Controller->DealDamage(30);
	}
	Detach();
}
