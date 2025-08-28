// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "WHealthBarComponent.generated.h"

UCLASS()
class WONDERLANDPROJECT_API UWHealthBarComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:
	void SetHealthBarPercent(float Percent);

private:
	UPROPERTY()
	class UWHealthBar* HealthBarWidget;
};
