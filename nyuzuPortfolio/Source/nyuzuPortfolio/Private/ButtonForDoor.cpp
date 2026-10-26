
#include "ButtonForDoor.h"
#include "DoorForButton.h"

AButtonForDoor::AButtonForDoor()
{
    PrimaryActorTick.bCanEverTick = false;
}

void AButtonForDoor::Interaction()
{
    if (!CanInteract())
    {
        return;
    }

    if (!IsValid(TargetDoor))
    {
        return;
    }

    TargetDoor->ReceiveSignal();
}
