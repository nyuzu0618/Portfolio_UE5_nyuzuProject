#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "InteractionCameraComponent.generated.h"

/**
 * インタラクト時のカメラ演出用カメラ
 * 付けた Actor がインタラクトされると、このカメラに切り替わる
 * ※1つの Actor にカメラはこれ1つだけにすること(ViewTarget は Actor 単位のため)
 */
UCLASS(ClassGroup = (Camera), meta = (BlueprintSpawnableComponent))
class NYUZUPORTFOLIO_API UInteractionCameraComponent : public UCameraComponent
{
    GENERATED_BODY()

public:
    // InteractInstigator(プレイヤーの Pawn か Controller)のカメラをこのカメラに切り替える
    UFUNCTION(BlueprintCallable, Category = "Interaction Camera")
    void PlayFor(AActor* InteractInstigator);

    // インタラクト時に自動で演出するか
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction Camera")
    bool bPlayOnInteract = true;

    // このカメラへ切り替える時間
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction Camera", meta = (ClampMin = "0.0"))
    float BlendTime = 2.0f;

    // 切り替え後にこのカメラに留まる時間(0 なら自動で戻らない)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction Camera", meta = (ClampMin = "0.0"))
    float HoldTime = 2.0f;

    // 元のカメラに戻る時間
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction Camera", meta = (ClampMin = "0.0"))
    float ReturnBlendTime = 1.5f;
};