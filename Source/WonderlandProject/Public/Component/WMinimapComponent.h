// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "WMinimapComponent.generated.h"

class USpringArmComponent;
class USceneCaptureComponent2D;
class UPaperSpriteComponent;
class UCanvasRenderTarget2D;
class UPaperSprite;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WONDERLANDPROJECT_API UWMinimapComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	UWMinimapComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Minimap)
	UTextureRenderTarget2D* RenderTarget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Minimap")
	bool bFollowRotation = true;

	void InitializeMinimap();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = Minimap)
	USpringArmComponent* MinimapCameraBoom;

	UPROPERTY(VisibleAnywhere, Category = Minimap)
	USceneCaptureComponent2D* MinimapCapture;
};
