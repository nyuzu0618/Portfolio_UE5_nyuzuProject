#include "Door.h"

ADoor::ADoor()
{
    PrimaryActorTick.bCanEverTick = true;

    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
}

void ADoor::BeginPlay()
{
    Super::BeginPlay();

    // 現在位置から上に200移動した位置を設定
    target_location = GetActorLocation() + FVector(0.0f, 0.0f, 200.0f);

    
}

void ADoor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (is_opening)
    {
        FVector current_location = GetActorLocation();

        FVector new_location = FMath::VInterpConstantTo(
            current_location,
            target_location,
            DeltaTime,
            open_speed
        );

        SetActorLocation(new_location);

        // 目標位置に到達したら停止
        if (current_location.Equals(target_location, 1.0f))
        {
            SetActorLocation(target_location);
            is_opening = false;
        }
    }
}

void ADoor::Open()
{
    if (!is_opening && !GetActorLocation().Equals(target_location, 1.0f))
    {
        is_opening = true;
    }
}