#pragma once

#include "CoreMinimal.h"
#include "HUDTypes.generated.h"

UENUM(BlueprintType)
enum class EHUDType : uint8
{
	InGame      UMETA(DisplayName = "InGame"),
	HP          UMETA(DisplayName = "HP"),
	Minimap     UMETA(DisplayName = "Minimap"),
	Interaction UMETA(DisplayName = "Interaction"),
};
