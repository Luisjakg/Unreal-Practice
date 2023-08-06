#include "RocketLauncherComponent.h"
#include "ProjectileRocket.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "A01_BlockoutShooterCharacter.h"
#include "A01_BlockoutShooter/A01_BlockoutShooter.h"

// Constructor
URocketLauncherComponent::URocketLauncherComponent()
{
	// Set default values for properties
	BarrelOffset = FVector(0, 0, 20);
}

void URocketLauncherComponent::Attach(AA01_BlockoutShooterCharacter* AttachCharacter)
{
	
	if(!AttachCharacter)
	{
		// print error message
		UE_LOG(LogTemp, Warning, TEXT("AttachCharacter is null!"));
		return;
	}
	Character = AttachCharacter;
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	AttachToComponent(Character->GetMesh(), AttachmentRules, FName("GunPoint"));
	SetRelativeRotation(FRotator(90,180,0));

	APlayerController* PlayerController = Cast<APlayerController>(Character->GetController());
	if(PlayerController)
	{
		UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if(SubSystem)
		{
			SubSystem->AddMappingContext(WeaponMappingContext,1);
		}
		UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent);
		if(EnhancedInputComponent)
		{
			EnhancedInputComponent->BindAction(PrimaryFireAction, ETriggerEvent::Started, this, &URocketLauncherComponent::Use);
		}
	}

	
	Super::Attach(AttachCharacter);
}

void URocketLauncherComponent::Detach()
{
	// Add your custom implementation here
	Super::Detach();
}

void URocketLauncherComponent::Use()
{
	FVector SpawnLocation = GetComponentLocation() + BarrelOffset + Character->GetActorForwardVector() * 100;
	FRotator SpawnRotation = GetComponentRotation();
	AProjectileRocket* SpawnedRocket = Cast<AProjectileRocket>(GetWorld()->SpawnActor(RocketClass, &SpawnLocation, &SpawnRotation));
	if(SpawnedRocket)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cast Worked!"));
		SpawnedRocket->Owner = Character;
		SpawnedRocket->FireInDirection(Character->GetActorForwardVector());
	}

	
	Super::Use();
}
