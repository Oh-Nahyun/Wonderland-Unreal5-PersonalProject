// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/DataTable.h"
#include "Other/Struct.h"
#include "WGameInstanceBase.generated.h"

UCLASS()
class WONDERLANDPROJECT_API UWGameInstanceBase : public UGameInstance
{
	GENERATED_BODY()

public:
	UWGameInstanceBase();

	UPROPERTY(BlueprintReadWrite)
	bool bIsGameSaved = false;

	UPROPERTY(BlueprintReadWrite, Category = "Tutorial")
	bool bIsTutorialEnd = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Quest")
	UDataTable* QuestDataTable;

	UPROPERTY(BlueprintReadWrite, Category = "Quest")
	TMap<FName, FQuestCompletedState> QuestStates;

	UPROPERTY(BlueprintReadWrite, Category = "Quest")
	TMap<FName, bool> QuestDeactivationStates;

	UFUNCTION(BlueprintPure, Category = "Quest")
	TArray<bool> GetStatesById(FName QuestId) const;

	UFUNCTION(BlueprintPure, Category = "Quest")
	bool IsQuestCompletedById(FName QuestId) const;

	UFUNCTION(BlueprintCallable, Category = "Quest")
	void SetObjectiveCompleted(FName QuestId, int32 ObjectiveIndex, bool isCompleted);

	UFUNCTION(BlueprintCallable, Category = "Quest")
	void EnsureAllQuestStatesByDT(bool isClearExisting = false);

	UFUNCTION(BlueprintCallable, Category = "Quest")
	void ChangeDeactivationState(FName QuestId);

private:
	int32 GetObjectiveCountFromDT(FName QuestId) const;
	void EnsureQuestObjectives(FName QuestId, int32 ObjectiveCount);
	static bool IsQuestCompleted(const FQuestCompletedState& State);
};
