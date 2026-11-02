#include "DoorForButton.h"
#include "IntearctInterface.h"

ADoorForButton::ADoorForButton()
{
    PrimaryActorTick.bCanEverTick = false;
}

void ADoorForButton::Interaction()
{
    // カメラ切り替え
    if (GetCanMoveCamera())
    {
        APlayerController* PC = GetWorld()->GetFirstPlayerController();

        IIntearctInterface* Interface =
            Cast<IIntearctInterface>(PC);

        if (Interface)
        {
            Interface->changeCamera(CameraComp, 2.0f, 2.0f);
        }
    }

    // 親クラスのドア開閉処理
    Super::Interaction();
}

void ADoorForButton::ReceiveSignal()
{
    if (!CanInteract())
    {
        return;
    }

    Interaction();
}