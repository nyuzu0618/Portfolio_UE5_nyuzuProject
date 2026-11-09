#pragma once

#include "CoreMinimal.h"
#include "ObjBase.h"
#include "Interactable.h"
#include "InteractableObjBase.generated.h"


/*
* インタラクト可能なオブジェクトの基礎クラス
*/

UCLASS()
class NYUZUPORTFOLIO_API AInteractableObjBase : public AObjBase , public  IInteractable
{
    GENERATED_BODY()

public:
    AInteractableObjBase();

    virtual bool CanInteract_Implementation(AActor* InteractInstigator) const override;
    virtual void Interact_Implementation(AActor* InteractInstigator) override;
    virtual FText GetInteractionText_Implementation() const override;

    /*
    *インタラクト自体の制御
    *イベントなどでインタラクトを止める・再開する 
    *例：イベントなどで使用を停止するチェック
    */
    UFUNCTION(BlueprintCallable, Category = "Interaction")
    void SetCanInteract(bool bNewCanInteract);

    // インタラクト機能自体が有効か(bCanInteract とオブジェクトの有効状態)
    UFUNCTION(BlueprintPure, Category = "Interaction")
    bool IsInteractionEnabled() const;

protected:
    

public:
    

protected:

    // インタラクト時の処理(C++ 派生クラス用)
    virtual void OnInteract(AActor* InteractInstigator) {}

    // インタラクト時の処理(BP 派生クラス用)
    UFUNCTION(BlueprintImplementableEvent, Category = "Interaction", meta = (DisplayName = "On Interact"))
    void BP_OnInteract(AActor* InteractInstigator);

    // InteractionCameraComponent を持っていればカメラ演出を行う
    void PlayInteractionCamera(AActor* InteractInstigator) const;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction")
    bool bCanInteract = true;

    // UI に表示する文言。空なら DisplayName を使う
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction")
    FText InteractionText;

};