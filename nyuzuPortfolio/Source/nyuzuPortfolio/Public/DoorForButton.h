
#pragma once

#include "CoreMinimal.h"
#include "DoorBase.h"
#include "DoorForButton.generated.h"

UCLASS()
class NYUZUPORTFOLIO_API ADoorForButton : public ADoorBase
{
    GENERATED_BODY()

public:
    ADoorForButton();

    UFUNCTION(BlueprintCallable, Category = "Signal")
    void ReceiveSignal();
};
