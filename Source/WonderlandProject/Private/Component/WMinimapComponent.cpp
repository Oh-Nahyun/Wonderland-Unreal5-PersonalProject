// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/WMinimapComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "PaperSpriteComponent.h"
#include "PaperSprite.h"
#include "Camera/CameraComponent.h"
#include "Components/SceneCaptureComponent2D.h"

UWMinimapComponent::UWMinimapComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	MinimapCameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("MinimapCameraBoom"));
	MinimapCameraBoom->SetupAttachment(this);
	MinimapCameraBoom->SetRelativeRotation(FRotator(-90.f, 0.f, 0.f));
	MinimapCameraBoom->TargetArmLength = 1700.f;
	MinimapCameraBoom->bUsePawnControlRotation = false;
	MinimapCameraBoom->bInheritPitch = false;
	MinimapCameraBoom->bInheritYaw = false;
	MinimapCameraBoom->bInheritRoll = false;

	MinimapCapture = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("MinimapCapture"));
	MinimapCapture->SetupAttachment(MinimapCameraBoom);
	MinimapCapture->ProjectionType = ECameraProjectionMode::Orthographic;
	MinimapCapture->OrthoWidth = 3072.f;
}

void UWMinimapComponent::BeginPlay()
{
	Super::BeginPlay();

	MinimapCameraBoom->AttachToComponent(GetOwner()->GetRootComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	InitializeMinimap();
}

void UWMinimapComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!GetOwner())
	{
		return;
	}

	FRotator OwnerRotation = GetOwner()->GetActorRotation();
	if (bFollowRotation)
	{
		MinimapCameraBoom->SetRelativeRotation(FRotator(-90.f, OwnerRotation.Yaw, 0.f));
	}
	else
	{
		MinimapCameraBoom->SetRelativeRotation(FRotator(-90.f, 0.f, 0.f));
	}
}

void UWMinimapComponent::InitializeMinimap()
{
	if (RenderTarget)
	{
		MinimapCapture->TextureTarget = RenderTarget;
	}
}
