

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "SignalReceiver.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USignalReceiver : public UInterface
{
	GENERATED_BODY()
};

/**
 * ボタンなどから信号を受け取るもののインターファイス
 */
class NYUZUPORTFOLIO_API ISignalReceiver
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	// Sender: 信号を送ったもの(ボタン)  InteractInstigator: 操作したプレイヤー
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Signal")
	void ReceiveSignal(AActor* Sender, AActor* InteractInstigator);
};
