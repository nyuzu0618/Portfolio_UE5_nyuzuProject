
#pragma once

#include "CoreMinimal.h"
#include "InteractableObjBase.h"
#include "Components/TimelineComponent.h"
#include "DoorBase.generated.h"

UENUM(BlueprintType)
enum class EMyDropdownSelection : uint8
{
    OptionA UMETA(DisplayName = "slide"),
    OptionB UMETA(DisplayName = "rotate"),
};

UCLASS()
class NYUZUPORTFOLIO_API ADoorBase : public AInteractableObjBase
{
    GENERATED_BODY()

public:
    ADoorBase();

    virtual void Interaction() override;

protected:
    virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door")
    EMyDropdownSelection DoorOpenSelection;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Door")
    FRotator OpenRotation = FRotator(0.0f, 90.0f, 0.0f);

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Door")
    FVector OpenLocation = FVector(0.0f, 0.0f, 100.0f);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door")
    float OpenSpeed = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Door")
    bool bStartsOpen = false;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Door")
    bool bIsOpen = false;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Door")
    TObjectPtr<UCurveFloat> DoorCurve;

    UPROPERTY(EditAnywhere, Category = "Door")
    class UCameraComponent* CameraComp;

private:
    UPROPERTY(VisibleAnywhere, Category = "Door")
    TObjectPtr<UTimelineComponent> DoorTimeline;

    FVector ClosedLocation;

    FRotator ClosedRotation;

    UFUNCTION()
    void UpdateDoor(float Value);

    void SlideOpen();

    void RotateOpen();
};
