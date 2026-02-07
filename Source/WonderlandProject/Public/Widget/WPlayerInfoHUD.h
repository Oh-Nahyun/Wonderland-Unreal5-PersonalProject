// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WPlayerInfoHUD.generated.h"

UCLASS()
class WONDERLANDPROJECT_API UWPlayerInfoHUD : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent)
	void SetHealthBar(float InHealthPercent);

	UFUNCTION(BlueprintImplementableEvent)
	void SetStaminaBar(float InStaminaPercent);
};
