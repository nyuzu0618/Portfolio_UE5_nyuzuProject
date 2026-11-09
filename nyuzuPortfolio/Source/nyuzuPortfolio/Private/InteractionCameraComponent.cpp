#include "InteractionCameraComponent.h"
#include "CameraControlInterface.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Controller.h"

void UInteractionCameraComponent::PlayFor(AActor* InteractInstigator)
{
    if (!IsValid(InteractInstigator))
    {
        return;
    }

    // Pawn が渡されたらその Controller、Controller が渡されたらそのまま使う
    AController* Controller = nullptr;

    if (const APawn* Pawn = Cast<APawn>(InteractInstigator))
    {
        Controller = Pawn->GetController();
    }
    else
    {
        Controller = Cast<AController>(InteractInstigator);
    }

    if (ICameraControlInterface* CameraControl = Cast<ICameraControlInterface>(Controller))
    {
        CameraControl->ChangeCamera(GetOwner(), BlendTime, HoldTime, ReturnBlendTime);
    }
}