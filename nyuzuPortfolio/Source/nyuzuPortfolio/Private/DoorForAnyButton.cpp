// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorForAnyButton.h"

ADoorForAnyButton::ADoorForAnyButton()
{

	bAllowDirectInteract = false;
	SetCanInteract(false);

}


void ADoorForAnyButton::ReceiveSignal_Implementation(AActor* Sender, AActor* InteractInstigator)
{
	SignalCounter++;

	if (SignalCounter >= SignalCounterMax)
	{
		if (SignalCounterMax == SignalCounter) 
		{
			Super::Open(Sender, InteractInstigator);
		}
	}


}

void ADoorForAnyButton::ClearCounter()
{
	SignalCounter = 0;
}