// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/WAnimInstance.h"
#include "Character/WPlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UWAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	AnimPlayerCharacter = Cast<AWPlayerCharacter>(TryGetPawnOwner());
	if (AnimPlayerCharacter)
	{
		PlayerCharacterMovement = AnimPlayerCharacter->GetCharacterMovement();
	}
}

void UWAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (PlayerCharacterMovement)
	{
		bIsPlayerAlive = AnimPlayerCharacter->GetCharacterAlive();
		PlayerCharacterSpeed = UKismetMathLibrary::VSizeXY(PlayerCharacterMovement->Velocity);
		bIsPlayerFalling = PlayerCharacterMovement->IsFalling();
		PlayerCharacterState = AnimPlayerCharacter->GetCharacterState();
	}
}
