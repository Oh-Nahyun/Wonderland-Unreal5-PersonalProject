#pragma once

UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	Unequipped,
	EquippedToyHammer
};

UENUM(BlueprintType)
enum class EActionState : uint8
{
	Unoccupied,
	Attacking
};

UENUM(BlueprintType)
enum class EDeathPoseType : uint8
{
	Alive,
	DeathLeft,
	DeathRight,
	DeathFront,
	DeathBack
};
