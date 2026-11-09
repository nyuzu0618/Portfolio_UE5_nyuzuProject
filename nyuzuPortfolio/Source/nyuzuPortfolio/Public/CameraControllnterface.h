

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "CameraControllnterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCameraControllnterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * カメラ演出を受け付けるもののインターファイス
 * PlayerContorollerで実装るする
 */
class NYUZUPORTFOLIO_API ICameraControllnterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	// NewViewTarget に切り替え、HoldTime 後に元のカメラへ戻す(HoldTime <= 0 なら戻さない)
	virtual void ChangeCamera(AActor* NewViewTarget, float BlendTime, float HoldTime, float ReturnBlendTime) = 0;

	// 元のカメラに戻す
	virtual void ReturnToDefaultCamera(float BlendTime) = 0;
	
};
