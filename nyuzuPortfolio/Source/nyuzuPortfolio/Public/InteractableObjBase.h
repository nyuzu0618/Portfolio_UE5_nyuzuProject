#pragma once

#include "CoreMinimal.h"
#include "ObjBase.h"
#include "InteractableObjBase.generated.h"

UCLASS()
class NYUZUPORTFOLIO_API AInteractableObjBase : public AObjBase
{
    GENERATED_BODY()

public:
    AInteractableObjBase();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction")
    bool bCanInteract = true;

public:
    //インタラクトの処理
    virtual void Interaction();

    /*インタラクトが使用可能化の制御
    例：鍵があるかのチェック*/
    virtual bool CanInteract() const;

    /*インタラクト自体の制御
    例：イベントなどで使用を停止するちぇえく*/
    void SetCanInteract(bool bNewCanInteract);

};