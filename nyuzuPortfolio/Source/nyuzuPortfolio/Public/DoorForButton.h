#pragma once

#include "CoreMinimal.h"
#include "DoorBase.h"
#include "DoorForButton.generated.h"

/**
 * ボタンからの信号でのみ開くドア
 */
UCLASS()
class NYUZUPORTFOLIO_API ADoorForButton : public ADoorBase
{
    GENERATED_BODY()

public:
    ADoorForButton();
};
