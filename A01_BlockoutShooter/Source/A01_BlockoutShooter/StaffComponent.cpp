// Fill out your copyright notice in the Description page of Project Settings.


#include "StaffComponent.h"

void UStaffComponent::Use()
{
	Super::Use();
	ServerBlaster();
}

void UStaffComponent::Detach()
{
	Super::Detach();
}

void UStaffComponent::Attach(AA01_BlockoutShooterCharacter* PickupCharacter)
{
	Super::Attach(PickupCharacter);
	if (!PickupCharacter)
	{
	   return;
    }

	Character = PickupCharacter;
	Character->HeldWeapon = this;

	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	AttachToComponent(Character->GetMesh(), AttachmentRules, FName("GunPoint"));
}

void UStaffComponent::ServerBlaster_Implementation()
{
	if(Character)
	{
		FVector ParticleVelocity = Character->GetFollowCamera()->GetForwardVector() * 2500;
		MulticastBlaster(ParticleVelocity);
	}
}

void UStaffComponent::MulticastBlaster_Implementation(FVector ParticleVelocity)
{
	if(NS_Blaster)
	{
		if(Character)
		{
			FVector SpawnLocation = GetComponentLocation() + Character->GetActorForwardVector() * 30;
			UNiagaraComponent* SpawnedEffect = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), NS_Blaster, SpawnLocation);
			if(SpawnedEffect)
			{
				SpawnedEffect->SetVariableVec3(FName("User.SpawnVelocity"), ParticleVelocity);
				SpawnedEffect->SetVariableObject(FName("User.ClassToTell"), this);
			}
		}
	}
}
