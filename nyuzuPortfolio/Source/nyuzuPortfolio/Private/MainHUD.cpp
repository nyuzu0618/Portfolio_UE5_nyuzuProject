#include "MainHUD.h"
#include "UI_Reticle.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"

void AMainHUD::BeginPlay()
{
    Super::BeginPlay();

    UE_LOG(LogTemp, Warning, TEXT("Into MainHUD::BeginPlay"));

    // レティクルのWBPを取得
    FString ReticlePath = TEXT("/Game/Holy/UI/WBP/WBP_Reticle.WBP_Reticle_C");

    TSubclassOf<UUserWidget> WidgetClass = TSoftClassPtr<UUserWidget>( FSoftObjectPath(ReticlePath) ).LoadSynchronous();

    if (!WidgetClass)
    {
        UE_LOG( LogTemp, Error, TEXT("Failed to load WBP_Reticle: %s"), *ReticlePath );
        return;
    }

    UE_LOG(LogTemp, Warning, TEXT("WBP_Reticle loaded successfully"));

    // PlayerControllerを取得
    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

    if (!PlayerController)
    {
        UE_LOG(LogTemp, Error, TEXT("PlayerController is nullptr"));
        return;
    }

    UE_LOG(LogTemp, Warning, TEXT("PlayerController acquired"));

    // Widgetを作成
    UUserWidget* UserWidget = CreateWidget<UUserWidget>(PlayerController, WidgetClass);

    if (!UserWidget)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to create Reticle Widget"));
        return;
    }

    UE_LOG(LogTemp, Warning, TEXT("Reticle Widget created"));

    // Viewportに追加
    UserWidget->AddToViewport(0);

    UE_LOG(LogTemp, Warning, TEXT("Reticle Widget added to Viewport"));
}