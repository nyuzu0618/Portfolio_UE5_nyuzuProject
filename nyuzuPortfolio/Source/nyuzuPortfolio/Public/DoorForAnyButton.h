#pragma once

#include "CoreMinimal.h"
#include "DoorBase.h"
#include "DoorForAnyButton.generated.h"

/**
 * 
 */
UCLASS()
class NYUZUPORTFOLIO_API ADoorForAnyButton : public ADoorBase
{
	GENERATED_BODY()

public:

	ADoorForAnyButton();

	// ISignalReceiver
	virtual void ReceiveSignal_Implementation(AActor* Sender, AActor* InteractInstigator) override;

public:

	UPROPERTY(EditAnywhere, Category = "Button")
	int SignalCounter = 0;

	UPROPERTY(EditAnywhere, Category = "Button")
	int SignalCounterMax = 0;

protected:
	UFUNCTION(BlueprintCallable, Category = "Button")
	void ClearCounter();

	UFUNCTION(BlueprintCallable, Category = "Button")
	void SetSignalCounter(int MaxCount);

	UFUNCTION(BlueprintCallable, Category = "Button")
	int GetCurrentSignalCount();

	UFUNCTION(BlueprintCallable, Category = "Button")
	bool SameObj = true;

	TArray<AActor*>Senders;
	//送信者をリストで保存してかぶってないかの確認
};
