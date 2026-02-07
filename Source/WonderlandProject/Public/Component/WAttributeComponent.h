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
	void IncreaseStaminaAtOnce(float InIncreaseStamina);
	void DecreaseStaminaAtOnce(float InDecreaseStamina);
	//void DecreaseStaminaSmooth(float InDecreaseStamina, float InDuration);
	//void DecreaseStaminaStep();
	bool IsAlive();
	bool IsEnergetic();
	bool IsRecoverStamina();

protected:
	virtual void BeginPlay() override;

private:
	//FTimerHandle StaminaDecreaseHandle;
	//float StaminaDecreasePerTick;
	//float StaminaGoal;

	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
	float CurrentHealth;

	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
	float MaxHealth;

	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
	float CurrentStamina;

	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
	float MaxStamina;
};
