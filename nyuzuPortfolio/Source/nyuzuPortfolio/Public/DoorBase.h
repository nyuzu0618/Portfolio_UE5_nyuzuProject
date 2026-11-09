#pragma once

#include "CoreMinimal.h"
#include "InteractableObjBase.h"
#include "SignalReceiver.h"
#include "DoorBase.generated.h"

class UTimelineComponent;
class UCurveFloat;
class UInteractionCameraComponent;

UENUM(BlueprintType)
enum class EDoorOpenType : uint8
{
    Slide  UMETA(DisplayName = "Slide"),
    Rotate UMETA(DisplayName = "Rotate"),
};

/**
 * 開閉するドア
 * 動くのは MeshComponent だけで、Actor 本体とカメラは動かない
 */
UCLASS()
class NYUZUPORTFOLIO_API ADoorBase : public AInteractableObjBase, public ISignalReceiver
{
    GENERATED_BODY()

public:
    ADoorBase();

    // IInteractable
    virtual bool CanInteract_Implementation(AActor* InteractInstigator) const override;

    // ISignalReceiver
    virtual void ReceiveSignal_Implementation(AActor* Sender, AActor* InteractInstigator) override;

    // 開いていれば閉じ、閉じていれば開く
    UFUNCTION(BlueprintCallable, Category = "Door")
    void ToggleDoor();

    UFUNCTION(BlueprintPure, Category = "Door")
    bool IsOpen() const { return bIsOpen; }

protected:
    virtual void BeginPlay() override;

    virtual void OnInteract(AActor* InteractInstigator) override;

    // 開き方(スライド / 回転)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door")
    EDoorOpenType OpenType = EDoorOpenType::Slide;

    // 開いたときの回転量(メッシュのローカル)
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Door", meta = (EditCondition = "OpenType == EDoorOpenType::Rotate"))
    FRotator OpenRotation = FRotator(0.0f, 90.0f, 0.0f);

    // 開いたときの移動量(Actor のローカル)
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Door", meta = (EditCondition = "OpenType == EDoorOpenType::Slide"))
    FVector OpenLocation = FVector(0.0f, 0.0f, 100.0f);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door", meta = (ClampMin = "0.01"))
    float OpenSpeed = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Door")
    bool bStartsOpen = false;

    // プレイヤーが直接インタラクトして開けられるか(false ならボタンなどの信号でのみ開く)
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Door")
    bool bAllowDirectInteract = true;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Door")
    bool bIsOpen = false;

    // 0 → 1 で閉 → 開
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Door")
    TObjectPtr<UCurveFloat> DoorCurve;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
    TObjectPtr<UInteractionCameraComponent> CameraComp;

private:
    UPROPERTY(VisibleAnywhere, Category = "Door")
    TObjectPtr<UTimelineComponent> DoorTimeline;

    FVector ClosedLocation = FVector::ZeroVector;
    FRotator ClosedRotation = FRotator::ZeroRotator;

    UFUNCTION()
    void UpdateDoor(float Alpha);

    // 開き具合(0〜1)をメッシュに反映する
    void ApplyDoorAlpha(float Alpha);
};
