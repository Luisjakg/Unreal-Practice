// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Components/TextBlock.h"
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
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

public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
};