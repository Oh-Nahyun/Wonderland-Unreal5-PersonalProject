#pragma once

#include "CoreMinimal.h"
#include "Struct.generated.h"

USTRUCT(BlueprintType)
struct FQuestCompletedState
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite)
    TArray<bool> ObjectiveCompleted;
};
