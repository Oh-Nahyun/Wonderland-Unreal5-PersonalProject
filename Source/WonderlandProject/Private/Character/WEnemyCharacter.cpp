// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/WEnemyCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Component/WAttributeComponent.h"
#include "Component/WHealthBarComponent.h"
#include "Kismet/KismetSystemLibrary.h"

AWEnemyCharacter::AWEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	GetMesh()->SetGenerateOverlapEvents(true);

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);

	Attribute = CreateDefaultSubobject<UWAttributeComponent>(TEXT("Attributes"));
	HealthBarWidget = CreateDefaultSubobject<UWHealthBarComponent>(TEXT("HealthBar"));
	HealthBarWidget->SetupAttachment(GetRootComponent());
}

void AWEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (HealthBarWidget)
	{
		HealthBarWidget->SetVisibility(false);
	}
}

void AWEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	/*
	if (CombatTarget)
	{
		const double DistanceToTarget = (CombatTarget->GetActorLocation() - GetActorLocation()).Size();
		if (DistanceToTarget > CombatRadius)
		{
			CombatTarget = nullptr;
			if (HealthBarWidget)
			{
				HealthBarWidget->SetVisibility(false);
			}
		}
	}
	*/
}

void AWEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float AWEnemyCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCanser)
{
	if (Attribute && HealthBarWidget)
	{
		Attribute->ReceiveDamage(DamageAmount);
		HealthBarWidget->SetHealthBarPercent(Attribute->GetHealthPercent());
	}
	CombatTarget = EventInstigator->GetPawn();
	return DamageAmount;
}

void AWEnemyCharacter::GetHit(const FVector& ImpactPoint) // _Implementation
{
	if (HealthBarWidget)
	{
		HealthBarWidget->SetVisibility(true);
	}

	DirectionalHitReact(ImpactPoint);
	if (Attribute && Attribute->IsAlive())
	{
		PlayHitReactMontage(HitPoseNumber);
	}
	else
	{
		Die(DeathPoseNumber);
	}
}

void AWEnemyCharacter::DirectionalHitReact(const FVector& ImpactPoint)
{
	const FVector Forward = GetActorForwardVector();
	const FVector ImpactLowered(ImpactPoint.X, ImpactPoint.Y, GetActorLocation().Z);
	const FVector ToHit = (ImpactLowered - GetActorLocation()).GetSafeNormal();
	const double CosTheta = FVector::DotProduct(Forward, ToHit);
	double Theta = FMath::Acos(CosTheta);
	Theta = FMath::RadiansToDegrees(Theta);

	const FVector CrossProduct = FVector::CrossProduct(Forward, ToHit);
	if (CrossProduct.Z < 0)
	{
		Theta *= -1.f;
	}

	if (Theta >= -135.f && Theta < -45.f)
	{
		HitPoseNumber = 0; // Left 0
		DeathPoseNumber = 1;
	}
	else if (Theta >= 45.f && Theta < 135.f)
	{
		HitPoseNumber = 1; // Right 1
		DeathPoseNumber = 0;
	}
	else if (Theta >= -45.f && Theta < 45.f)
	{
		HitPoseNumber = 2; // Front 2
		DeathPoseNumber = 2;
	}
	else
	{
		HitPoseNumber = 3; // Back 3
		DeathPoseNumber = 3;
	}

	UKismetSystemLibrary::DrawDebugArrow(this, GetActorLocation(), GetActorLocation() + CrossProduct * 100.f, 5.f, FColor::Blue, 5.f);
	UKismetSystemLibrary::DrawDebugArrow(this, GetActorLocation(), GetActorLocation() + Forward * 60.f, 5.f, FColor::Red, 5.f);
	UKismetSystemLibrary::DrawDebugArrow(this, GetActorLocation(), GetActorLocation() + ToHit * 60.f, 5.f, FColor::Green, 5.f);
}

void AWEnemyCharacter::PlayHitReactMontage(int32 InSelection)
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && HitReactMontage)
	{
		AnimInstance->Montage_Play(HitReactMontage);
		FName SectionName = FName();
		switch (InSelection)
		{
		case 0:
			SectionName = FName("HitFromLeft");
			break;
		case 1:
			SectionName = FName("HitFromRight");
			break;
		case 2:
			SectionName = FName("HitFromFront");
			break;
		case 3:
			SectionName = FName("HitFromBack");
			break;
		default:
			break;
		}
		AnimInstance->Montage_JumpToSection(SectionName, HitReactMontage);
	}
}

void AWEnemyCharacter::Die(int32 InSelection)
{
	if (HealthBarWidget)
	{
		HealthBarWidget->SetVisibility(false);
	}

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && DeathMontage)
	{
		AnimInstance->Montage_Play(DeathMontage);
		FName SectionName = FName();
		switch (InSelection)
		{
		case 0:
			SectionName = FName("DieFromLeft");
			DeathPose = EDeathPoseType::DeathLeft;
			break;
		case 1:
			SectionName = FName("DieFromRight");
			DeathPose = EDeathPoseType::DeathRight;
			break;
		case 2:
			SectionName = FName("DieFromFront");
			DeathPose = EDeathPoseType::DeathFront;
			break;
		case 3:
			SectionName = FName("DieFromBack");
			DeathPose = EDeathPoseType::DeathBack;
			break;
		default:
			break;
		}
		AnimInstance->Montage_JumpToSection(SectionName, DeathMontage);
	}

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetLifeSpan(3.f);
}
