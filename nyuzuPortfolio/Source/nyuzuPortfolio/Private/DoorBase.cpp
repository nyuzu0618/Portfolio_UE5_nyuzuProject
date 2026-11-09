#include "DoorBase.h"
#include "InteractionCameraComponent.h"
#include "Components/TimelineComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Curves/CurveFloat.h"
#include "nyuzuPortfolio.h"

ADoorBase::ADoorBase()
{
    DoorTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("DoorTimeline"));

    if (UStaticMeshComponent* Mesh = GetMeshComponent())
    {
        Mesh->SetMobility(EComponentMobility::Movable);
    }

    // ルートに付けるので、メッシュが動いてもカメラは動かない
    CameraComp = CreateDefaultSubobject<UInteractionCameraComponent>(TEXT("CameraComponent"));
    CameraComp->SetupAttachment(RootComponent);
}

void ADoorBase::BeginPlay()
{
    Super::BeginPlay();

    // 動かすのはメッシュなので、メッシュのローカル座標を閉じた状態として保存する
    if (UStaticMeshComponent* Mesh = GetMeshComponent())
    {
        ClosedLocation = Mesh->GetRelativeLocation();
        ClosedRotation = Mesh->GetRelativeRotation();
    }

    if (DoorCurve)
    {
        FOnTimelineFloat UpdateFunction;
        UpdateFunction.BindUFunction(this, GET_FUNCTION_NAME_CHECKED(ADoorBase, UpdateDoor));

        DoorTimeline->AddInterpFloat(DoorCurve, UpdateFunction);
        DoorTimeline->SetLooping(false);
    }
    else
    {
        UE_LOG(LognyuzuPortfolio, Warning, TEXT("%s: DoorCurve is not set"), *GetName());
    }

    bIsOpen = bStartsOpen;

    if (bIsOpen)
    {
        ApplyDoorAlpha(1.0f);

        if (DoorCurve)
        {
            DoorTimeline->SetPlaybackPosition(DoorTimeline->GetTimelineLength(), false, false);
        }
    }
}

bool ADoorBase::CanInteract_Implementation(AActor* InteractInstigator) const
{
    return bAllowDirectInteract && Super::CanInteract_Implementation(InteractInstigator);
}

void ADoorBase::OnInteract(AActor* InteractInstigator)
{
    Super::OnInteract(InteractInstigator);

    ToggleDoor();
}

void ADoorBase::ReceiveSignal_Implementation(AActor* Sender, AActor* InteractInstigator)
{
    Open(Sender ,InteractInstigator);
}

void ADoorBase::Open(AActor* Sender, AActor* InteractInstigator)
{
    // 信号の場合は bAllowDirectInteract を見ない
    if (!IsInteractionEnabled())
    {
        return;
    }

    PlayInteractionCamera(InteractInstigator);
    ToggleDoor();
}

void ADoorBase::ToggleDoor()
{
    if (!DoorCurve)
    {
        UE_LOG(LognyuzuPortfolio, Warning, TEXT("%s: Cannot toggle door because DoorCurve is not set"), *GetName());
        return;
    }

    bIsOpen = !bIsOpen;

    DoorTimeline->SetPlayRate(OpenSpeed);

    if (bIsOpen)
    {
        DoorTimeline->Play();
    }
    else
    {
        DoorTimeline->Reverse();
    }
}

void ADoorBase::UpdateDoor(float Alpha)
{
    ApplyDoorAlpha(Alpha);
}

void ADoorBase::ApplyDoorAlpha(float Alpha)
{
    UStaticMeshComponent* Mesh = GetMeshComponent();
    if (!Mesh)
    {
        return;
    }

    switch (OpenType)
    {
    case EDoorOpenType::Slide:
        Mesh->SetRelativeLocation(ClosedLocation + OpenLocation * Alpha);
        break;

    case EDoorOpenType::Rotate:
        Mesh->SetRelativeRotation(ClosedRotation + OpenRotation * Alpha);
        break;
    }
}
