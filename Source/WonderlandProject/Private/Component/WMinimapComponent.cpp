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
    SetMobility(EComponentMobility::Movable);
}

void UWMinimapComponent::OnRegister()
{
    Super::OnRegister();

    AActor* Owner = GetOwner();
    if (!Owner) return;

    if (!MinimapCameraBoom)
    {
        const FName BoomName = MakeUniqueObjectName(Owner, USpringArmComponent::StaticClass(), TEXT("MinimapCameraBoom"));
        MinimapCameraBoom = NewObject<USpringArmComponent>(Owner, BoomName);

        Owner->AddInstanceComponent(MinimapCameraBoom);
        MinimapCameraBoom->SetupAttachment(this);
        MinimapCameraBoom->SetMobility(EComponentMobility::Movable);
        MinimapCameraBoom->SetUsingAbsoluteLocation(false);
        MinimapCameraBoom->SetUsingAbsoluteRotation(false);
        MinimapCameraBoom->SetRelativeRotation(FRotator(-90.f, 0.f, 0.f));
        MinimapCameraBoom->TargetArmLength = 1700.f;
        MinimapCameraBoom->bUsePawnControlRotation = false;
        MinimapCameraBoom->bInheritPitch = false;
        MinimapCameraBoom->bInheritYaw = false;
        MinimapCameraBoom->bInheritRoll = false;
        MinimapCameraBoom->RegisterComponent();
    }
    else
    {
        MinimapCameraBoom->AttachToComponent(this, FAttachmentTransformRules::KeepRelativeTransform);
        if (!MinimapCameraBoom->IsRegistered())
            MinimapCameraBoom->RegisterComponent();
    }

    if (!MinimapCapture)
    {
        const FName CaptureName = MakeUniqueObjectName(Owner, USceneCaptureComponent2D::StaticClass(), TEXT("MinimapCapture"));
        MinimapCapture = NewObject<USceneCaptureComponent2D>(Owner, CaptureName);

        Owner->AddInstanceComponent(MinimapCapture);
        MinimapCapture->SetupAttachment(MinimapCameraBoom);
        MinimapCapture->SetMobility(EComponentMobility::Movable);
        MinimapCapture->SetUsingAbsoluteLocation(false);
        MinimapCapture->SetUsingAbsoluteRotation(false);
        MinimapCapture->ProjectionType = ECameraProjectionMode::Orthographic;
        MinimapCapture->OrthoWidth = 3072.f;
        MinimapCapture->RegisterComponent();
    }
    else
    {
        MinimapCapture->AttachToComponent(MinimapCameraBoom, FAttachmentTransformRules::KeepRelativeTransform);
        if (!MinimapCapture->IsRegistered())
            MinimapCapture->RegisterComponent();
    }

    InitializeMinimap();
}

void UWMinimapComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    AActor* Owner = GetOwner();
    if (!Owner || !MinimapCameraBoom)
    {
        return;
    }

    if (bFollowRotation)
    {
        const FRotator OwnerRotation = Owner->GetActorRotation();
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