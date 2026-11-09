#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CameraControlInterface.generated.h"

UINTERFACE(MinimalAPI, meta = (CannotImplementInterfaceInBlueprint))
class UCameraControlInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * カメラ演出を受け付けるもの(PlayerController)が実装するインターフェース
 */
class NYUZUPORTFOLIO_API ICameraControlInterface
{
	GENERATED_BODY()

public:
	// NewViewTarget に切り替え、HoldTime 後に元のカメラへ戻す(HoldTime <= 0 なら戻さない)
	virtual void ChangeCamera(AActor* NewViewTarget, float BlendTime, float HoldTime, float ReturnBlendTime) = 0;

	// 元のカメラに戻す
	virtual void ReturnToDefaultCamera(float BlendTime) = 0;
};
