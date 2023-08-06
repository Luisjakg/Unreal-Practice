// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TextBlock.h"
#include "Blueprint/UserWidget.h"
#include "ShooterGameState.h"
#include "ScoreWidget.generated.h"


/**
 * 
 */
UCLASS()
class A01_BLOCKOUTSHOOTER_API UScoreWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TeamOneScore;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TeamTwoScore;

	AShooterGameState* GameState;

public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
};
