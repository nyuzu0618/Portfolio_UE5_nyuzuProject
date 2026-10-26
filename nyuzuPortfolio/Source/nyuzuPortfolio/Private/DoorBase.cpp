
#include "DoorBase.h"
#include "Camera/CameraComponent.h"

ADoorBase::ADoorBase()
{
    PrimaryActorTick.bCanEverTick = false;

    DoorTimeline = CreateDefaultSubobject<UTimelineComponent>( TEXT("DoorTimeline") );

    CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CamearaComponent"));
}

void ADoorBase::BeginPlay()
{
    Super::BeginPlay();

    ClosedLocation = GetActorLocation();
    ClosedRotation = GetActorRotation();

    if (DoorCurve)
    {
        FOnTimelineFloat update_function;

        update_function.BindUFunction( this, FName("UpdateDoor") );

        DoorTimeline->AddInterpFloat( DoorCurve, update_function );

        DoorTimeline->SetLooping(false);
    }

    bIsOpen = bStartsOpen;

    if (bIsOpen)
    {
        if (DoorOpenSelection == EMyDropdownSelection::OptionA)
        {
            SetActorLocation(ClosedLocation + OpenLocation);
        }
        else
        {
            SetActorRotation(ClosedRotation + OpenRotation);
        }

        if (DoorCurve)
        {
            DoorTimeline->SetPlaybackPosition( DoorTimeline->GetTimelineLength(), false, false );
        }
    }
}

void ADoorBase::Interaction()
{
    if (!CanInteract() || !DoorCurve)
    {
        return;
    }

    bIsOpen = !bIsOpen;

    DoorTimeline->SetPlayRate(OpenSpeed);

    if (bIsOpen)
    {
        switch (DoorOpenSelection)
        {
        case EMyDropdownSelection::OptionA:
            SlideOpen();
            break;

        case EMyDropdownSelection::OptionB:
            RotateOpen();
            break;
        }
    }
    else
    {
        DoorTimeline->Reverse();
    }
}

void ADoorBase::SlideOpen()
{
    DoorTimeline->Play();
}

void ADoorBase::RotateOpen()
{
    DoorTimeline->Play();
}

void ADoorBase::UpdateDoor(float Value )
{

    if (DoorOpenSelection == EMyDropdownSelection::OptionA)
    {
        FVector target_location = ClosedLocation + OpenLocation * Value;

        SetActorLocation(target_location);
    }
    else if (DoorOpenSelection == EMyDropdownSelection::OptionB)
    {
        FRotator target_rotation = ClosedRotation + OpenRotation * Value;

        SetActorRotation(target_rotation);
    }
}
