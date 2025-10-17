// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/WPlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/BoxComponent.h"
#include "Component/WAttributeComponent.h"
#include "Component/WMinimapComponent.h"
#include "Blueprint/UserWidget.h"
#include "Item/WItem.h"
#include "Weapon/WToyHammer.h"
#include "Animation/AnimMontage.h"

AWPlayerCharacter::AWPlayerCharacter()
{
 	PrimaryActorTick.bCanEverTick = true;

	// Character Controller Rotation Setting
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	// Character Movement Setting
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);

	// Components
	Attribute = CreateDefaultSubobject<UWAttributeComponent>(TEXT("Attributes"));
	MinimapComponent = CreateDefaultSubobject<UWMinimapComponent>(TEXT("MinimapComponent"));
	MinimapComponent->SetupAttachment(GetRootComponent());
}

void AWPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	SetWeaponCollisionEnabled(ECollisionEnabled::NoCollision);
	if (PlayerInfoWidgetClass)
	{
		PlayerInfoHUD = CreateWidget<UWPlayerInfoHUD>(GetWorld(), PlayerInfoWidgetClass);
		if (PlayerInfoHUD)
		{
			PlayerInfoHUD->AddToViewport();
		}
	}
}

void AWPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bIsEnergetic || bCanIncreaseStamina)
	{
		IncreaseStamina(NormalIncreaseStamina);
	}

	if (bCanDecreaseStamina)
	{
		DecreaseStamina(RunDecreaseStamina);
	}
}

void AWPlayerCharacter::SetWeaponCollisionEnabled(ECollisionEnabled::Type InCollisionEnabled)
{
	if (EquippedWeapon && EquippedWeapon->GetWeaponBox())
	{
		EquippedWeapon->GetWeaponBox()->SetCollisionEnabled(InCollisionEnabled);
		EquippedWeapon->IgnoreActors.Empty();
	}
}

void AWPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Action Mapping
	PlayerInputComponent->BindAction(FName("Jump"), IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(FName("Run"), IE_Pressed, this, &AWPlayerCharacter::LeftShiftPressed);
	PlayerInputComponent->BindAction(FName("Run"), IE_Released, this, &AWPlayerCharacter::LeftShiftReleased);
	PlayerInputComponent->BindAction(FName("Equip"), IE_Pressed, this, &AWPlayerCharacter::FKeyPressed);
	PlayerInputComponent->BindAction(FName("Attack"), IE_Pressed, this, &AWPlayerCharacter::MouseLeftButtonPressed);

	// Axis Mapping
	PlayerInputComponent->BindAxis(FName("MoveForward"), this, &AWPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis(FName("MoveRight"), this, &AWPlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis(FName("Turn"), this, &AWPlayerCharacter::Turn);
	PlayerInputComponent->BindAxis(FName("LookUp"), this, &AWPlayerCharacter::LookUp);
}

float AWPlayerCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCanser)
{
	if (Attribute)
	{
		Attribute->ReceiveDamage(DamageAmount);
		PlayerInfoHUD->SetHealthBar(Attribute->GetHealthPercent());
		bIsAlive = Attribute->IsAlive();
	}
	return DamageAmount;
}

void AWPlayerCharacter::SetAfterPlayerDie()
{
	UE_LOG(LogTemp, Warning, TEXT("[Player] Die")); /////////////////////////
}

void AWPlayerCharacter::DecreaseStamina(float InDecreaseStamineAmount)
{
	if (Attribute)
	{
		if (bIsEnergetic)
		{
			bIsEnergetic = Attribute->IsEnergetic();
		}
		Attribute->DecreaseStaminaAtOnce(InDecreaseStamineAmount);
		PlayerInfoHUD->SetStaminaBar(Attribute->GetStaminaPercent());
	}
}

void AWPlayerCharacter::IncreaseStamina(float InIncreaseStamineAmount)
{
	if (Attribute)
	{
		if (!bIsEnergetic)
		{
			bIsEnergetic = Attribute->IsRecoverStamina();
		}
		Attribute->IncreaseStaminaAtOnce(InIncreaseStamineAmount);
		PlayerInfoHUD->SetStaminaBar(Attribute->GetStaminaPercent());
	}
}

void AWPlayerCharacter::LeftShiftPressed()
{
	if (!bIsEnergetic)
	{
		return;
	}

	bIsRunMode = true;
	if (bCanIncreaseStamina)
	{
		bCanIncreaseStamina = false;
	}
	if (!bCanDecreaseStamina)
	{
		bCanDecreaseStamina = true;
	}
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	DecreaseStamina(RunDecreaseStamina);
}

void AWPlayerCharacter::LeftShiftReleased()
{
	if (!bIsEnergetic)
	{
		return;
	}

	bIsRunMode = false;
	if (!bCanIncreaseStamina)
	{
		bCanIncreaseStamina = true;
	}
	if (bCanDecreaseStamina)
	{
		bCanDecreaseStamina = false;
	}
	GetCharacterMovement()->MaxWalkSpeed = 400.f;
}

void AWPlayerCharacter::FKeyPressed()
{
	AWToyHammer* OverlappingWeapon = Cast<AWToyHammer>(OverlappingItem);
	if (OverlappingItem)
	{
		OverlappingWeapon->Equip(GetMesh(), FName("RightHandSocket"), this, this);
		CharacterState = ECharacterState::EquippedToyHammer;
		EquippedWeapon = OverlappingWeapon;
	}
}

void AWPlayerCharacter::MouseLeftButtonPressed()
{
	if (!bIsEnergetic || ActionState != EActionState::Unoccupied)
	{
		return;
	}

	if (CharacterState == ECharacterState::Unequipped)
	{
		PlayAttackMontage(PunchAttackMontage, PunchAttackSelection);
		DecreaseStamina(PunchAttackDecreaseStamina);
	}
	else if (CharacterState == ECharacterState::EquippedToyHammer)
	{
		const int32 ToyHammerAttackSelection = FMath::RandRange(0, 1);
		PlayAttackMontage(ToyHammerAttackMontage, ToyHammerAttackSelection);
		DecreaseStamina(ToyHammerAttackDecreaseStamina);
	}

	if (bCanIncreaseStamina)
	{
		bCanIncreaseStamina = false;
	}
	ActionState = EActionState::Attacking;
}

float AWPlayerCharacter::GetWeaponSocketSpeed() const
{
	if (GetMesh())
	{
		FVector WeaponVelocity = GetMesh()->GetBoneLinearVelocity("RightHandSocket");
		return WeaponVelocity.Size();
	}
	return 0.0f;
}

FVector AWPlayerCharacter::GetWeaponForceDirection() const
{
	if (GetMesh())
	{
		return GetMesh()->GetBoneLinearVelocity("RightHandSocket").GetSafeNormal();
	}
	return FVector::ZeroVector;
}

void AWPlayerCharacter::PlayAttackMontage(UAnimMontage* InMontage, int32 InSelection)
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && InMontage)
	{
		AnimInstance->Montage_Play(InMontage);
		FName SectionName = FName();
		switch (InSelection)
		{
		case 0:
			SectionName = FName("Attack1");
			PunchAttackSelection = 1;
			break;
		case 1:
			SectionName = FName("Attack2");
			PunchAttackSelection = 0;
			break;
		default:
			break;
		}
		AnimInstance->Montage_JumpToSection(SectionName, InMontage);
	}
}

void AWPlayerCharacter::AttackEnd()
{
	if (!bIsRunMode)
	{
		bCanIncreaseStamina = true;
	}
	else
	{
		bCanIncreaseStamina = false;
	}
	ActionState = EActionState::Unoccupied;
}

void AWPlayerCharacter::BlackOut()
{
	if (bIsEnergetic)
	{
		return;
	}

	bIsRunMode = false;
	bCanIncreaseStamina = true;
	bCanDecreaseStamina = false;
	GetCharacterMovement()->MaxWalkSpeed = 400.f;
}

void AWPlayerCharacter::MoveForward(float InValue)
{
	if (Controller && (InValue != 0.f))
	{
		const FRotator ControlRotation = GetControlRotation();
		const FRotator YawRotation(0.f, ControlRotation.Yaw, 0.f);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, InValue);
	}
}

void AWPlayerCharacter::MoveRight(float InValue)
{
	if (Controller && (InValue != 0.f))
	{
		const FRotator ControlRotation = GetControlRotation();
		const FRotator YawRotation(0.f, ControlRotation.Yaw, 0.f);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, InValue);
	}
}

void AWPlayerCharacter::Turn(float InValue)
{
	AddControllerYawInput(InValue);
}

void AWPlayerCharacter::LookUp(float InValue)
{
	AddControllerPitchInput(InValue);
}
