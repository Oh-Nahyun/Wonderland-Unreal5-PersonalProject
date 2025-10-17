// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/WAttributeComponent.h"

UWAttributeComponent::UWAttributeComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UWAttributeComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UWAttributeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UWAttributeComponent::ReceiveDamage(float InDamage)
{
	CurrentHealth = FMath::Clamp(CurrentHealth - InDamage, 0.f, MaxHealth);
}

void UWAttributeComponent::IncreaseStaminaAtOnce(float InIncreaseStamina)
{
	CurrentStamina = FMath::Clamp(CurrentStamina + InIncreaseStamina, 0.f, MaxStamina);
}

void UWAttributeComponent::DecreaseStaminaAtOnce(float InDecreaseStamina)
{
	CurrentStamina = FMath::Clamp(CurrentStamina - InDecreaseStamina, 0.f, MaxStamina);
}

//void UWAttributeComponent::DecreaseStaminaSmooth(float InDecreaseStamina, float InDuration)
//{
//	StaminaGoal = FMath::Clamp(CurrentStamina - InDecreaseStamina, 0.f, MaxStamina);
//	float TotalDecrease = CurrentStamina - StaminaGoal;
//	int32 TickCount = InDuration / 0.05f;
//	StaminaDecreasePerTick = TotalDecrease / TickCount;
//
//	GetWorld()->GetTimerManager().ClearTimer(StaminaDecreaseHandle);
//	GetWorld()->GetTimerManager().SetTimer(StaminaDecreaseHandle, this, &UWAttributeComponent::DecreaseStaminaStep, 0.05f, true);
//}
//
//void UWAttributeComponent::DecreaseStaminaStep()
//{
//	CurrentStamina -= StaminaDecreasePerTick;
//	if (CurrentStamina <= StaminaGoal + 0.01f)
//	{
//		CurrentStamina = StaminaGoal;
//		GetWorld()->GetTimerManager().ClearTimer(StaminaDecreaseHandle);
//	}
//}

float UWAttributeComponent::GetHealthPercent()
{
	return CurrentHealth / MaxHealth;
}

float UWAttributeComponent::GetStaminaPercent()
{
	return CurrentStamina / MaxStamina;
}

bool UWAttributeComponent::IsAlive()
{
	return CurrentHealth > 0.f;
}

bool UWAttributeComponent::IsEnergetic()
{
	return CurrentStamina > 0.f;
}

bool UWAttributeComponent::IsRecoverStamina()
{
	return CurrentStamina >= MaxStamina;
}
