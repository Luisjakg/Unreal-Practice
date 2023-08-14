// Fill out your copyright notice in the Description page of Project Settings.


#include "ClubComponent.h"



void UClubComponent::Use()
{
	Super::Use();
	ServerBonk();
}

void UClubComponent::Detach()
{
	Super::Detach();
}

void UClubComponent::Attach(AA01_BlockoutShooterCharacter* PickupCharacter)
{
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

void UClubComponent::ServerBonk_Implementation()
{
	TArray<FHitResult> HitResults;
	const FVector Start = Character->GetActorLocation();
	const FVector End = Start + Character->GetActorForwardVector() * 100;
	const FCollisionShape CubeShape = FCollisionShape::MakeBox(FVector(100));
	const bool Sweep = GetWorld()->SweepMultiByChannel(HitResults, End, End, Character->GetActorQuat(), ECC_Pawn, CubeShape);
	for(auto HitResult : HitResults)
	{
		if(HitResult.GetActor() != Character)
		{
			AA01_BlockoutShooterCharacter* HitCharacter = Cast<AA01_BlockoutShooterCharacter>(HitResult.GetActor());
			if(HitCharacter)
			{
				HitCharacter->LaunchCharacter(((HitResult.GetActor()->GetActorLocation() - Character->GetActorLocation()).GetSafeNormal() +
			   HitResult.GetActor()->GetActorUpVector()/1.5).GetSafeNormal() * 1500, false, false);
				HitCharacter->DealDamage(30);
			}
		}
	}
}
