#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bottun.generated.h"

class AnyuzuPortfolioCharacter;
class ADoor;
class UStaticMeshComponent;

UCLASS()
class NYUZUPORTFOLIO_API ABottun : public AActor
{
    GENERATED_BODY()

public:
    ABottun();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

public:
    AnyuzuPortfolioCharacter* player_character;

    AActor* look_actor;

    ADoor* target;

    UPROPERTY(EditAnywhere)
    TObjectPtr<UStaticMeshComponent>Mesh;

public:
    void Interaction();
};