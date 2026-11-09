#include "MainHUD.h"
#include "Blueprint/UserWidget.h"
#include "nyuzuPortfolio.h"

void AMainHUD::BeginPlay()
{
	Super::BeginPlay();

    for (const TPair<EHUDType, TSubclassOf<UUserWidget>>& Pair : WidgetClasses)
    {
        CreateHUDWidget(Pair.Key, Pair.Value);
    }
}

UUserWidget* AMainHUD::CreateHUDWidget(EHUDType UIType, TSubclassOf<UUserWidget> WidgetClass)
{
    if (!WidgetClass)
    {
        UE_LOG(LognyuzuPortfolio, Warning, TEXT("WidgetClass is not set: %s"), *UEnum::GetValueAsString(UIType));
        return nullptr;
    }

    APlayerController* PC = GetOwningPlayerController();
    if (!PC)
    {
        UE_LOG(LognyuzuPortfolio, Error, TEXT("Owning PlayerController is null"));
        return nullptr;
    }

    UUserWidget* Widget = CreateWidget<UUserWidget>(PC, WidgetClass);
    if (!Widget)
    {
        UE_LOG(LognyuzuPortfolio, Error, TEXT("Failed to create widget: %s"), *UEnum::GetValueAsString(UIType));
        return nullptr;
    }

    Widget->AddToViewport();
    HUDWidgets.Add(UIType, Widget);

    UE_LOG(LognyuzuPortfolio, Verbose, TEXT("Created widget: %s"), *UEnum::GetValueAsString(UIType));
    return Widget;
}

void AMainHUD::SetUIVisibility(EHUDType UIType, bool bVisible)
{
    UUserWidget* Widget = GetHUDWidget(UIType);
    if (!Widget)
    {
        UE_LOG(LognyuzuPortfolio, Warning, TEXT("Widget not found: %s"), *UEnum::GetValueAsString(UIType));
        return;
    }

    Widget->SetVisibility(bVisible
        ? ESlateVisibility::HitTestInvisible
        : ESlateVisibility::Collapsed);
}

void AMainHUD::SetAllUIVisibility(bool bVisible)
{
    for (const TPair<EHUDType, TObjectPtr<UUserWidget>>& Pair : HUDWidgets)
    {
        SetUIVisibility(Pair.Key, bVisible);
    }
}

UUserWidget* AMainHUD::GetHUDWidget(EHUDType UIType) const
{
    return HUDWidgets.FindRef(UIType);
}