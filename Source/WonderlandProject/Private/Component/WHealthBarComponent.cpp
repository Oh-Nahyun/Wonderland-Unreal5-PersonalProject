// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/WHealthBarComponent.h"
#include "Widget/WHealthBar.h"
#include "Components/ProgressBar.h"

void UWHealthBarComponent::SetHealthBarPercent(float Percent)
{
	if (HealthBarWidget == nullptr)
	{
		HealthBarWidget = Cast<UWHealthBar>(GetUserWidgetObject());
	}

	if (HealthBarWidget && HealthBarWidget->HealthBar)
	{
		HealthBarWidget->HealthBar->SetPercent(Percent);
	}
}
