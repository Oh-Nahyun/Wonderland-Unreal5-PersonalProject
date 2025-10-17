// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/WHitInterface.h"
#include "Other/Enum.h"
#include "WEnemyCharacter.generated.h"

class UWAttributeComponent;
class UWHealthBarComponent;

UCLASS()
class WONDERLANDPROJECT_API AWEnemyCharacter : public ACharacter, public IWHitInterface
{
	GENERATED_BODY()

public:
	AWEnemyCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
							 class AController* EventInstigator, AActor* DamageCanser) override;
	virtual void GetHit(const FVector& ImpactPoint) override; // _Implementation
	void DirectionalHitReact(const FVector& ImpactPoint);

protected:
	virtual void BeginPlay() override;
	void Die(int32 InSelection);

	UPROPERTY(BlueprintReadOnly)
	EDeathPoseType DeathPose = EDeathPoseType::Alive;

	int32 HitPoseNumber = 0;
	int32 DeathPoseNumber = 0;

private:
	void PlayHitReactMontage(int32 InSelection);

	UPROPERTY(VisibleAnywhere, Category = Components)
	UWAttributeComponent* Attribute;

	UPROPERTY(VisibleAnywhere, Category = Widgets)
	UWHealthBarComponent* HealthBarWidget;

	UPROPERTY(EditDefaultsOnly, Category = Montage)
	UAnimMontage* HitReactMontage;

	UPROPERTY(EditDefaultsOnly, Category = Montage)
	UAnimMontage* DeathMontage;

	UPROPERTY()
	AActor* CombatTarget;

	UPROPERTY(EditAnywhere)
	double CombatRadius = 100.f;
};
