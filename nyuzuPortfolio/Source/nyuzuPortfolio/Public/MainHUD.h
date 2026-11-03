#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HUDInterface.h"
#include "MainHUD.generated.h"

class UUserWidget;

UCLASS()
class NYUZUPORTFOLIO_API AMainHUD : public AHUD, public IHUDInterface
{
    GENERATED_BODY()

public:

    virtual void SetUIVisibility(
        EHUDType UIType,
        bool bVisible
    ) override;

protected:

    UPROPERTY()
    TObjectPtr<UUserWidget> ReticleWidget;

    UPROPERTY()
    TObjectPtr<UUserWidget> HPWidget;

    UPROPERTY()
    TObjectPtr<UUserWidget> MinimapWidget;

    UPROPERTY()
    TObjectPtr<UUserWidget> InteractionWidget;
};