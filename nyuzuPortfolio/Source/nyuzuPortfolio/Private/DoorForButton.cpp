
#include "DoorForButton.h"

ADoorForButton::ADoorForButton()
{
    PrimaryActorTick.bCanEverTick = false;
}

void ADoorForButton::ReceiveSignal()
{
    if (!CanInteract())
    {
        return;
    }

    Interaction();
}
