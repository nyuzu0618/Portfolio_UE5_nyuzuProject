// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableObjBase.h"
#include "ButtonBase.generated.h"

/**
 * 押すとtargetsに信号を送るボタン
 * TargetsにはSignalReceiverを実装したActorを指定する
 */
UCLASS()
class NYUZUPORTFOLIO_API AButtonBase : public AInteractableObjBase
{
    GENERATED_BODY()

public:
    virtual void OnInteract(AActor* InteractInstigator) override;

    // 信号を送る対象
    UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Button")
    TArray<TObjectPtr<AActor>> Targets;
};
