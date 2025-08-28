// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "WHitInterface.generated.h"

UINTERFACE(MinimalAPI)
class UWHitInterface : public UInterface
{
	GENERATED_BODY()
};

class WONDERLANDPROJECT_API IWHitInterface
{
	GENERATED_BODY()

public:
	//UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	virtual void GetHit(const FVector& ImpactPoint) = 0;
};
