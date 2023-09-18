// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "NiagaraDataInterfaceExport.h"
#include "ScoreWidget.h"
#include "ItemComponent.h"
#include "BlasterExplosion.h"
#include "NiagaraFunctionLibrary.h"
#include "Net/UnrealNetwork.h"
#include "ShooterGameState.h"
#include "A01_BlockoutShooterCharacter.generated.h"


UCLASS(config=Game)
class AA01_BlockoutShooterCharacter : public ACharacter, public INiagaraParticleCallbackHandler
{
	GENERATED_BODY()
	
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

public:
	AA01_BlockoutShooterCharacter();
	
protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);
	
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UScoreWidget> ScoreWidgetClass;

	UPROPERTY(EditAnywhere)
     float MaxHealth = 100;
    UPROPERTY(EditAnywhere)
     float CurrentHealth;
	
	UItemComponent* HeldWeapon;
	
    void DealDamage(int Damage);
    void Respawn();

	AShooterGameState* GameState;

	UPROPERTY(EditAnywhere)
	UInputAction* PrimaryFireAction;

	void FireWeapon();
		
    UFUNCTION(Server, Reliable)
	void ServerFireWeapon();

	UPROPERTY(EditAnywhere)
	UNiagaraSystem* NS_DeathParticle;
	
	FVector DeathParticleOffset = FVector(0,0,-75);
	 
	UFUNCTION(NetMulticast, Reliable)
	void DeathParticles();

	virtual void ReceiveParticleData_Implementation(const TArray
		<FBasicParticleData>& Data, UNiagaraSystem*NiagaraSystem,
		const FVector& SimulationPositionOffsetoverride) override;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<ABlasterExplosion> BlasterExplosionClass;
	
	UFUNCTION(Server, Reliable)
	void ServerSpawnExplosion(const TArray<FBasicParticleData>& Data);

	FTimerHandle InvulnerabilityTimer;
    UMaterialInterface* DefaultMaterialInstanceOne;
    UMaterialInterface* DefaultMaterialInstanceTwo;
    bool bIsPlayerInvulnerable = false;

	UFUNCTION()
	void StartInvulnerabilityTimer();
	void DisableVulnerability();	
	
	UFUNCTION(Server, Reliable)
	void ServerDisableInvulnerability();

	UFUNCTION(NetMulticast, Reliable)
	void UpdateMaterials(UMaterialInterface* NewMaterial);

};

