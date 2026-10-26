
#pragma once

#include "CoreMinimal.h"
#include "ButtonBase.h"
#include "ButtonForDoor.generated.h"

class ADoorForButton;

UCLASS()
class NYUZUPORTFOLIO_API AButtonForDoor : public AButtonBase
{
    GENERATED_BODY()

public:
    AButtonForDoor();

    virtual void Interaction() override;

protected:
    UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Button")
    TObjectPtr<ADoorForButton> TargetDoor;
};
