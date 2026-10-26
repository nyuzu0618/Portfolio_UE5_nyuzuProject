
#include "ButtonBase.h"

AButtonBase::AButtonBase()
{
    PrimaryActorTick.bCanEverTick = false;
}

void AButtonBase::Interaction()
{
    if (!CanInteract())
    {
        return;
    }

    // ボタン共通の処理が必要になった場合はここに追加する。
}
