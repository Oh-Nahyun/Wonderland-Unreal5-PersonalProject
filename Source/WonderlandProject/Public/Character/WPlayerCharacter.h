// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Other/Enum.h"
#include "GameFramework/Character.h"
#include "Widget/WPlayerInfoHUD.h"
#include "WPlayerCharacter.generated.h"

class AWItem;
class AWToyHammer; /////
class UAnimMontage;
class UWAttributeComponent;
class UWMinimapComponent;

UCLASS()
class WONDERLANDPROJECT_API AWPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AWPlayerCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
							 class AController* EventInstigator, AActor* DamageCanser) override;

	UPROPERTY(BlueprintReadWrite, Category = State)
	bool bIsRunMode = false;

	UPROPERTY(EditDefaultsOnly, Category = Montage)
	UAnimMontage* PunchAttackMontage;

	UPROPERTY(EditDefaultsOnly, Category = Montage)
	UAnimMontage* ToyHammerAttackMontage;

	UPROPERTY(EditDefaultsOnly, Category = Montage)
	UAnimMontage* HitReactMontage;

	UFUNCTION(BlueprintCallable)
	void SetWeaponCollisionEnabled(ECollisionEnabled::Type InCollisionEnabled);

	UFUNCTION(BlueprintCallable)
	void SetAfterPlayerDie();

	float GetWeaponSocketSpeed() const;
	FVector GetWeaponForceDirection() const;

protected:
	virtual void BeginPlay() override;
	void DecreaseStamina(float InDecreaseStamineAmount);
	void IncreaseStamina(float InIncreaseStamineAmount);

	// Action Functions
	void LeftShiftPressed();
	void LeftShiftReleased();
	void FKeyPressed();
	void MouseLeftButtonPressed();

	// Axis Functions
	void MoveForward(float InValue);
	void MoveRight(float InValue);
	void Turn(float InValue);
	void LookUp(float InValue);

private:
	AWItem* OverlappingItem;
	AWToyHammer* EquippedWeapon; /////
	int32 PunchAttackSelection = 0;
	void PlayAttackMontage(UAnimMontage* InMontage, int32 InSelection);

	ECharacterState CharacterState = ECharacterState::Unequipped;
	
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EActionState ActionState = EActionState::Unoccupied;

	UFUNCTION(BlueprintCallable)
	void AttackEnd();

	UPROPERTY(VisibleAnywhere, Category = Components)
	UWAttributeComponent* Attribute;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bIsAlive = true;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bIsEnergetic = true;

	UFUNCTION(BlueprintCallable)
	void BlackOut();

	UPROPERTY(VisibleAnywhere, Category = Components)
	UWMinimapComponent* MinimapComponent;

	UPROPERTY(EditAnywhere, Category = Widgets)
	TSubclassOf<UWPlayerInfoHUD> PlayerInfoWidgetClass;

	UPROPERTY(EditAnywhere, Category = Widgets)
	UWPlayerInfoHUD* PlayerInfoHUD;

	float NormalIncreaseStamina = 0.1f;
	float RunDecreaseStamina = 0.1f;
	float PunchAttackDecreaseStamina = 5.0f;
	float ToyHammerAttackDecreaseStamina = 10.0f;

	bool bCanIncreaseStamina = true;
	bool bCanDecreaseStamina = false;

public:
	FORCEINLINE void SetOverlappingItem(AWItem* InItem) { OverlappingItem = InItem; }
	FORCEINLINE bool GetCharacterAlive() const { return bIsAlive; }
	FORCEINLINE ECharacterState GetCharacterState() const { return CharacterState; }
};
