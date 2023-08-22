// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/BoxComponent.h"
#include "Field/FieldSystemComponent.h"
#include "Field/FieldSystemObjects.h"
#include "CoreMinimal.h"
#include "Field/FieldSystemActor.h"
#include "AnchorField.generated.h"

/**
 * 
 */
UCLASS()
class A01_BLOCKOUTSHOOTER_API AAnchorField : public AFieldSystemActor
{
	GENERATED_BODY()

public:
	AAnchorField();
	UPROPERTY(EditAnywhere)
	UBoxComponent* BoxCollision;
	
	UPROPERTY(EditAnywhere)
	UBoxFalloff* BoxFalloff;
	
	UPROPERTY(EditAnywhere)
	UUniformInteger* UniformInteger;
	
	UPROPERTY(EditAnywhere)
	UCullingField* CullingField;

	virtual void OnConstruction(const FTransform& Transform) override;

};
