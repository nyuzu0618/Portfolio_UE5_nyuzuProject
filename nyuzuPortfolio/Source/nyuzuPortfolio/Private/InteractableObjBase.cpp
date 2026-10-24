
#include "InteractableObjBase.h"

AInteractableObjBase::AInteractableObjBase()
{
    
}

void AInteractableObjBase::BeginPlay()
{
    Super::BeginPlay();
}

void AInteractableObjBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// インタラクトの処理
void AInteractableObjBase::Interaction()
{
    if (!CanInteract())
    {
        return;
    }

    // インタラクト可能な場合の共通処理
}

// インタラクトが使用可能か判定
bool AInteractableObjBase::CanInteract() const
{
    return bCanInteract;
}

// インタラクトの使用状態を変更
void AInteractableObjBase::SetCanInteract(bool bNewCanInteract)
{
    bCanInteract = bNewCanInteract;
}
