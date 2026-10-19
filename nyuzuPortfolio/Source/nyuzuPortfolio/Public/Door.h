#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"

class UStaticMeshComponent;

UCLASS()
class NYUZUPORTFOLIO_API ADoor : public AActor
{
    GENERATED_BODY()

public:
    ADoor();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    // ドアを開く
    void Open();

private:
    // 開いたときの移動先
    FVector target_location;

    // 開く速さ
    float open_speed = 200.0f;

    // 開いているか
    bool is_opening = false;

    UPROPERTY(EditAnywhere)
    TObjectPtr<UStaticMeshComponent>Mesh;
};