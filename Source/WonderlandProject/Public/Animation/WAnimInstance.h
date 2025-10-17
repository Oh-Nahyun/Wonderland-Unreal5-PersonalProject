// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Other/Enum.h"
#include "Animation/AnimInstance.h"
#include "WAnimInstance.generated.h"

class AWPlayerCharacter;
class UCharacterMovementComponent;

UCLASS()
class WONDERLANDPROJECT_API UWAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaTime) override;

	UPROPERTY(BlueprintReadOnly, Category = PlayerCharacter)
	AWPlayerCharacter* AnimPlayerCharacter;

	UPROPERTY(BlueprintReadOnly, Category = PlayerCharacter)
	UCharacterMovementComponent* PlayerCharacterMovement;

	UPROPERTY(BlueprintReadOnly, Category = PlayerCharacter)
	float PlayerCharacterSpeed;

	UPROPERTY(BlueprintReadOnly, Category = PlayerCharacter)
	bool bIsPlayerFalling;

	UPROPERTY(BlueprintReadOnly, Category = PlayerCharacter)
	bool bIsPlayerAlive;

	UPROPERTY(BlueprintReadOnly, Category = PlayerCharacter)
	ECharacterState PlayerCharacterState;
};
