
#include "ButtonBase.h"
#include "SignalReceiver.h"
#include "nyuzuPortfolio.h"

void AButtonBase::OnInteract(AActor* InteractInstigator)
{
    Super::OnInteract(InteractInstigator);

    for (AActor* Target : Targets)
    {
        if (!IsValid(Target))
        {
            continue;
        }

        if (!Target->Implements<USignalReceiver>())
        {
            UE_LOG(LognyuzuPortfolio, Warning, TEXT("%s: Target %s does not implement SignalReceiver"),
                *GetName(), *Target->GetName());
            continue;
        }

        ISignalReceiver::Execute_ReceiveSignal(Target, this, InteractInstigator);
    }
}

