// Copyright Epic Games, Inc. All Rights Reserved.

#include "A01_BlockoutShooterCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "EnhancedInputSubsystems.h"
#include "ItemComponent.h"
#include "GameFramework/PlayerState.h"


//////////////////////////////////////////////////////////////////////////
// AA01_BlockoutShooterCharacter

AA01_BlockoutShooterCharacter::AA01_BlockoutShooterCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)

	
}

void AA01_BlockoutShooterCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
	
	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	if(ScoreWidgetClass)
	{
		UScoreWidget* ScoreWidget = Cast<UScoreWidget>(CreateWidget(GetGameInstance(), ScoreWidgetClass));
		ScoreWidget->AddToViewport();
	}

	GameState = Cast<AShooterGameState>(GetWorld()->GetGameState());
}

void AA01_BlockoutShooterCharacter::DealDamage(int Damage)
{
	CurrentHealth-=Damage;
	UE_LOG(LogTemp, Warning, TEXT("Hit %s New Health: %f"), *GetName(), CurrentHealth);
	if(CurrentHealth<= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s Died!"), *GetName());
		Respawn();
	}
}

void AA01_BlockoutShooterCharacter::Respawn()
{
	
	APlayerState* MyPlayerState = GetPlayerState();
	if (HeldWeapon)
    {
    	HeldWeapon->GetOwner()->Destroy();
    }
	if(HasAuthority())
	{
		DeathParticles();
	}
	Destroy();
	GameState->PlayerScored(MyPlayerState);
	GameState->RestartPlayer(MyPlayerState);
}

void AA01_BlockoutShooterCharacter::FireWeapon()
{
	if (HeldWeapon)
    {
    	ServerFireWeapon();
    }

}

void AA01_BlockoutShooterCharacter::ReceiveParticleData_Implementation(const TArray<FBasicParticleData>& Data,
	UNiagaraSystem* NiagaraSystem, const FVector& SimulationPositionOffsetoverride)
{
	INiagaraParticleCallbackHandler::ReceiveParticleData_Implementation(
		Data, NiagaraSystem, SimulationPositionOffsetoverride);

	if(HasAuthority())
	{
		ServerSpawnExplosion(Data);
	}
}

void AA01_BlockoutShooterCharacter::ServerSpawnExplosion_Implementation(const TArray<FBasicParticleData>& Data)
{
	for(int i = 0; i < Data.Num(); i++)
	{
		if(BlasterExplosionClass)
		{
			ABlasterExplosion* SpawnedExplosion = Cast<ABlasterExplosion>(GetWorld()->SpawnActor(BlasterExplosionClass,&Data[i].Position));
			if(SpawnedExplosion)
			{
				SpawnedExplosion->VelocityAmount = 1000;
				SpawnedExplosion->StrainAmount = 500000;
				SpawnedExplosion->SetActorLocation(Data[i].Position);
				SpawnedExplosion->Explode();
			}
		}
	}
}

void AA01_BlockoutShooterCharacter::DeathParticles_Implementation()
{
	if(NS_DeathParticle)
	{
		
		FVector SpawnLocation = this->GetActorLocation() + DeathParticleOffset;
		FLinearColor ParticleColor = GameState->GetTeamColour(GetPlayerState());
		float ParticleScale = FMath::Lerp(1.0f, 3.0f, GameState->GetScoreRatio(GetPlayerState()));
		UNiagaraComponent* ParticleComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), NS_DeathParticle,
		 SpawnLocation, this->GetActorRotation());
		ParticleComponent->SetNiagaraVariableLinearColor(FString("SkullColor"),ParticleColor);
		ParticleComponent->SetNiagaraVariableFloat(FString("SkullScale"), ParticleScale);
	}
}

void AA01_BlockoutShooterCharacter::ServerFireWeapon_Implementation()
{
	HeldWeapon->Use();
}

//////////////////////////////////////////////////////////////////////////
// Input

void AA01_BlockoutShooterCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AA01_BlockoutShooterCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AA01_BlockoutShooterCharacter::Look);

		//Primary Fire
		EnhancedInputComponent->BindAction(PrimaryFireAction, ETriggerEvent::Started, this, &AA01_BlockoutShooterCharacter::FireWeapon);
	}

}

void AA01_BlockoutShooterCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AA01_BlockoutShooterCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}




