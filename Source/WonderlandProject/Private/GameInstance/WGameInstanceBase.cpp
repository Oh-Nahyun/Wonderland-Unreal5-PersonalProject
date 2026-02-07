// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstance/WGameInstanceBase.h"
#include "Other/Struct.h"

UWGameInstanceBase::UWGameInstanceBase()
{
}

/// <summary>
/// 세부 퀘스트 완료 상태 조회하는 함수
/// </summary>
TArray<bool> UWGameInstanceBase::GetStatesById(FName QuestId) const
{
	const FQuestCompletedState* S = QuestStates.Find(QuestId);
	if (!S)
	{
		return {};
	}
	return S->ObjectiveCompleted;
}

/// <summary>
/// 퀘스트 완료 여부 조회하는 함수
/// </summary>
bool UWGameInstanceBase::IsQuestCompletedById(FName QuestId) const
{
	const FQuestCompletedState* S = QuestStates.Find(QuestId);
	bool isQuestCompleted = S ? IsQuestCompleted(*S) : false;

	return isQuestCompleted;
}

/// <summary>
/// 세부 퀘스트 완료 상태 변경하는 함수
/// </summary>
void UWGameInstanceBase::SetObjectiveCompleted(FName QuestId, int32 ObjectiveIndex, bool isCompleted)
{
	const int32 ObjectiveCount = GetObjectiveCountFromDT(QuestId);
	EnsureQuestObjectives(QuestId, ObjectiveCount);

	FQuestCompletedState* S = QuestStates.Find(QuestId);
	if (!S || !S->ObjectiveCompleted.IsValidIndex(ObjectiveIndex))
	{
		return;
	}

	S->ObjectiveCompleted[ObjectiveIndex] = isCompleted;
}

/// <summary>
/// 데이터 테이블 기준으로 초기화하는 함수
/// </summary>
void UWGameInstanceBase::EnsureAllQuestStatesByDT(bool isClearExisting)
{
	if (!QuestDataTable)
	{
		return;
	}

	if (isClearExisting)
	{
		QuestStates.Empty();
	}

	const TArray<FName> RowNames = QuestDataTable->GetRowNames();
	for (const FName& QuestId : RowNames)
	{
		const int32 Count = GetObjectiveCountFromDT(QuestId);
		EnsureQuestObjectives(QuestId, Count);

		QuestDeactivationStates.Add(QuestId, false);
	}
}

/// <summary>
/// 퀘스트 활성화 여부 변경하는 함수
/// </summary>
void UWGameInstanceBase::ChangeDeactivationState(FName QuestId)
{
	QuestDeactivationStates.FindOrAdd(QuestId) = true;
}

/// <summary>
/// 데이터 테이블에서 세부 퀘스트 갯수 가져오는 함수
/// </summary>
int32 UWGameInstanceBase::GetObjectiveCountFromDT(FName QuestId) const
{
	if (!QuestDataTable)
	{
		return 0;
	}

	const UScriptStruct* RowStruct = QuestDataTable->GetRowStruct();
	const uint8* RowData = QuestDataTable->FindRowUnchecked(QuestId);
	if (!RowStruct || !RowData)
	{
		return 0;
	}

	const FArrayProperty* ObjectivesProp = nullptr;
	for (TFieldIterator<FArrayProperty> It(RowStruct); It; ++It)
	{
		if (It->GetName().StartsWith(TEXT("Objectives")))
		{
			ObjectivesProp = *It;
			break;
		}
	}

	if (!ObjectivesProp)
	{
		return 0;
	}

	const void* ArrayPtr = ObjectivesProp->ContainerPtrToValuePtr<void>(RowData);
	FScriptArrayHelper Helper(ObjectivesProp, ArrayPtr);

	return Helper.Num();
}

/// <summary>
/// 세부 퀘스트 갯수 보정하는 함수
/// </summary>
void UWGameInstanceBase::EnsureQuestObjectives(FName QuestId, int32 ObjectiveCount)
{
	if (ObjectiveCount <= 0)
	{
		return;
	}

	FQuestCompletedState& S = QuestStates.FindOrAdd(QuestId);
	const int32 OldNum = S.ObjectiveCompleted.Num();
	if (OldNum == ObjectiveCount)
	{
		return;
	}

	S.ObjectiveCompleted.SetNum(ObjectiveCount);

	for (int32 i = OldNum; i < ObjectiveCount; i++)
	{
		S.ObjectiveCompleted[i] = false;
	}
}

/// <summary>
/// 전체 완료 판정하는 함수
/// </summary>
bool UWGameInstanceBase::IsQuestCompleted(const FQuestCompletedState& State)
{
	if (State.ObjectiveCompleted.Num() == 0)
	{
		return false;
	}

	for (bool isDone : State.ObjectiveCompleted)
	{
		if (!isDone) return false;
	}
	return true;
}
