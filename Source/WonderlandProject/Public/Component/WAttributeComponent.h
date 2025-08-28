// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WAttributeComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WONDERLANDPROJECT_API UWAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UWAttributeComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	float GetHealthPercent();
	float GetStaminaPercent();
	void ReceiveDamage(float InDamage);
	void DecreaseStamina(float InDecreaseStamina);
	void IncreaseStamina(float InIncreaseStamina);
	bool IsAlive();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
	float CurrentHealth;

	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
	float MaxHealth;

	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
	float CurrentStamina;

	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
	float MaxStamina;
};
