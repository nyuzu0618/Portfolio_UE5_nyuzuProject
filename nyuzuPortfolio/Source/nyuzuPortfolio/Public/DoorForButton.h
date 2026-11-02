
#pragma once

#include "CoreMinimal.h"
#include "DoorBase.h"
#include "DoorForButton.generated.h"

class IIntearctInterface;

UCLASS()
class NYUZUPORTFOLIO_API ADoorForButton : public ADoorBase
{
    GENERATED_BODY()

public:
    ADoorForButton();

    void Interaction() override;

    UFUNCTION(BlueprintCallable, Category = "Signal")
    void ReceiveSignal();
};
