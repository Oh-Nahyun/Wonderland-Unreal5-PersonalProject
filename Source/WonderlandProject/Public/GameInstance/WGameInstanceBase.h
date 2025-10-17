// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "WGameInstanceBase.generated.h"

UCLASS()
class WONDERLANDPROJECT_API UWGameInstanceBase : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UWGameInstanceBase();

	// void SaveGame();
};
