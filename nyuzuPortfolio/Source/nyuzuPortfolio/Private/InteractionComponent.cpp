#include "InteractionComponent.h"
#include "Interactable.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Controller.h"
#include "Engine/World.h"

UInteractionComponent::UInteractionComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

AActor* UInteractionComponent::FindInteractableActor() const
{
    const APawn* OwnerPawn = Cast<APawn>(GetOwner());
    if (!OwnerPawn)
    {
        return nullptr;
    }

    const AController* Controller = OwnerPawn->GetController();
    if (!Controller)
    {
        return nullptr;
    }

    FVector ViewLocation;
    FRotator ViewRotation;
    Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);

    const FVector TraceEnd = ViewLocation + ViewRotation.Vector() * InteractRange;

    FCollisionQueryParams QueryParams(SCENE_QUERY_STAT(InteractionTrace), false, OwnerPawn);
    FHitResult HitResult;

    if (!GetWorld()->LineTraceSingleByChannel(HitResult, ViewLocation, TraceEnd, TraceChannel, QueryParams))
    {
        return nullptr;
    }

    AActor* HitActor = HitResult.GetActor();

    if (IsValid(HitActor) && HitActor->Implements<UInteractable>())
    {
        return HitActor;
    }

    return nullptr;
}

bool UInteractionComponent::TryInteract()
{
    AActor* Target = FindInteractableActor();
    if (!Target)
    {
        return false;
    }

    AActor* InteractInstigator = GetOwner();

    if (!IInteractable::Execute_CanInteract(Target, InteractInstigator))
    {
        return false;
    }

    IInteractable::Execute_Interact(Target, InteractInstigator);
    return true;
}