

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "Interactable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

/**
 * プレイヤーがインタラクトできるもののインターフェイス
 * IInteractable::Execute_Interact(Actor, Insigator)のように実装する予定
 */
class NYUZUPORTFOLIO_API IInteractable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
    // 今インタラクトできるか(鍵の所持チェックなど)
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
    bool CanInteract(AActor* InteractInstigator) const;

    // インタラクトの実行
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
    void Interact(AActor* InteractInstigator);

    // UI に表示する文言(「ドアを開ける」など)
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
    FText GetInteractionText() const;
};
