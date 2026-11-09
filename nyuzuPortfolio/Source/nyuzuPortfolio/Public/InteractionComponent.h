#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/EngineTypes.h"
#include "InteractionComponent.generated.h"

/**
 * プレイヤーが見ているものを探してインタラクトするコンポーネント
 * Pawn に付けて使う
 */
UCLASS(ClassGroup = (Interaction), meta = (BlueprintSpawnableComponent))
class NYUZUPORTFOLIO_API UInteractionComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UInteractionComponent();

    // 視線の先にあるインタラクト可能な Actor を返す(なければ nullptr)
    UFUNCTION(BlueprintCallable, Category = "Interaction")
    AActor* FindInteractableActor() const;

    // 視線の先のものにインタラクトする。成功したら true
    UFUNCTION(BlueprintCallable, Category = "Interaction")
    bool TryInteract();

protected:
    // インタラクトできる距離
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction", meta = (ClampMin = "0.0"))
    float InteractRange = 300.0f;

    // トレースに使うチャンネル(専用チャンネルを作ったらそれを指定する)
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction")
    TEnumAsByte<ECollisionChannel> TraceChannel = ECC_Visibility;
};