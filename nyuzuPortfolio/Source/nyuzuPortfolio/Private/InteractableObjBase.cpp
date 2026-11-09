
#include "InteractableObjBase.h"
#include "InteractionCameraComponent.h"

AInteractableObjBase::AInteractableObjBase()
{
    
}

bool AInteractableObjBase::CanInteract_Implementation(AActor* InteractInstigator) const
{
    return IsInteractionEnabled();
}

// インタラクトの処理
void AInteractableObjBase::Interact_Implementation(AActor* InteractInstigator)
{
    // チェックはここで1回だけ行う
    if (!IInteractable::Execute_CanInteract(this, InteractInstigator))
    {
        return;
    }

    PlayInteractionCamera(InteractInstigator);

    OnInteract(InteractInstigator);
    BP_OnInteract(InteractInstigator);
}

// インタラクトの使用状態を変更
void AInteractableObjBase::SetCanInteract(bool bNewCanInteract)
{
    bCanInteract = bNewCanInteract;
}

FText AInteractableObjBase::GetInteractionText_Implementation() const
{
    return InteractionText.IsEmpty() ? GetObjectDisplayName() : InteractionText;
}

bool AInteractableObjBase::IsInteractionEnabled() const
{
    return bCanInteract && IsObjectActive();
}

void AInteractableObjBase::PlayInteractionCamera(AActor* InteractInstigator) const
{
    UInteractionCameraComponent* InteractionCamera = FindComponentByClass<UInteractionCameraComponent>();

    if (InteractionCamera && InteractionCamera->bPlayOnInteract)
    {
        InteractionCamera->PlayFor(InteractInstigator);
    }
}