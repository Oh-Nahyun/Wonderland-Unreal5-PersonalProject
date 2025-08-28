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

void UWAttributeComponent::DecreaseStamina(float InDecreaseStamina)
{
	CurrentStamina = FMath::Clamp(CurrentStamina - InDecreaseStamina, 0.f, MaxStamina);
}

void UWAttributeComponent::IncreaseStamina(float InIncreaseStamina)
{
	CurrentStamina = FMath::Clamp(CurrentStamina + InIncreaseStamina, 0.f, MaxStamina);
}

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
