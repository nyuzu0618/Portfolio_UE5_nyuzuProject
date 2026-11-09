#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HUDTypes.h" 
#include "MainHUD.generated.h"

class UUserWidget;

UCLASS()
class NYUZUPORTFOLIO_API AMainHUD : public AHUD
{
    GENERATED_BODY()

public:

    // UIの表示・非表示
	UFUNCTION(BlueprintCallable, Category = "HUD")
    virtual void SetUIVisibility(EHUDType UIType, bool bVisible);

    //すべてのUIの表示・非表示
	UFUNCTION(BlueprintCallable, Category = "HUD")  
	void SetAllUIVisibility(bool bVisible);

	UFUNCTION(BlueprintPure, Category = "HUD")
	UUserWidget* GetHUDWidget(EHUDType UIType) const;

protected:

    virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "HUD")
	TMap<EHUDType, TSubclassOf<UUserWidget>> WidgetClasses;

private:

    // Widgetを作成して登録する
    UUserWidget* CreateHUDWidget(EHUDType UIType, TSubclassOf<UUserWidget> WidgetClass);

    // UIタイプとWidgetを紐づけて管理
    UPROPERTY(Transient)
    TMap<EHUDType, TObjectPtr<UUserWidget>> HUDWidgets;
};