#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HUDInterface.generated.h"

UENUM(BlueprintType)
enum class EHUDType : uint8
{
    Reticle     UMETA(DisplayName = "Reticle"),
    HP          UMETA(DisplayName = "HP"),
    Minimap     UMETA(DisplayName = "Minimap"),
    Interaction UMETA(DisplayName = "Interaction"),
    All         UMETA(DisplayName = "All")
};

UINTERFACE(MinimalAPI, Blueprintable)
class UHUDInterface : public UInterface
{
    GENERATED_BODY()
};

class NYUZUPORTFOLIO_API IHUDInterface
{
    GENERATED_BODY()

public:

    virtual void SetUIVisibility(EHUDType UIType, bool bVisible) = 0;
};