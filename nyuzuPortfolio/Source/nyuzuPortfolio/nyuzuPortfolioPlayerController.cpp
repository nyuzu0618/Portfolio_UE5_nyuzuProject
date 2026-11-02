// Copyright Epic Games, Inc. All Rights Reserved.


#include "nyuzuPortfolioPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "InputMappingContext.h"
#include "nyuzuPortfolioCameraManager.h"
#include "Blueprint/UserWidget.h"
#include "Camera/CameraComponent.h"
#include "TimerManager.h"
#include "nyuzuPortfolio.h"
#include "Widgets/Input/SVirtualJoystick.h"

AnyuzuPortfolioPlayerController::AnyuzuPortfolioPlayerController()
{
	// set the player camera manager class
	PlayerCameraManagerClass = AnyuzuPortfolioCameraManager::StaticClass();
}

void AnyuzuPortfolioPlayerController::BeginPlay()
{
	Super::BeginPlay();

	
	// only spawn touch controls on local player controllers
	if (ShouldUseTouchControls() && IsLocalPlayerController())
	{
		// spawn the mobile controls widget
		MobileControlsWidget = CreateWidget<UUserWidget>(this, MobileControlsWidgetClass);

		if (MobileControlsWidget)
		{
			// add the controls to the player screen
			MobileControlsWidget->AddToPlayerScreen(0);

		} else {

			UE_LOG(LognyuzuPortfolio, Error, TEXT("Could not spawn mobile controls widget."));

		}

	}
}

void AnyuzuPortfolioPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// only add IMCs for local player controllers
	if (IsLocalPlayerController())
	{
		// Add Input Mapping Context
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			for (UInputMappingContext* CurrentContext : DefaultMappingContexts)
			{
				Subsystem->AddMappingContext(CurrentContext, 0);
			}

			// only add these IMCs if we're not using mobile touch input
			if (!ShouldUseTouchControls())
			{
				for (UInputMappingContext* CurrentContext : MobileExcludedMappingContexts)
				{
					Subsystem->AddMappingContext(CurrentContext, 0);
				}
			}
		}
	}
	
}

bool AnyuzuPortfolioPlayerController::ShouldUseTouchControls() const
{
	// are we on a mobile platform? Should we force touch?
	return SVirtualJoystick::ShouldDisplayTouchInterface() || bForceTouchControls;
}

void AnyuzuPortfolioPlayerController::changeCamera(
    UCameraComponent* targetCamera,
    float moveTime,
    float returnTime)
{
    if (!targetCamera)
    {
        return;
    }

    GetWorldTimerManager().ClearTimer(cameraReturnTimer);

    previousViewTarget = GetViewTarget();

    SetViewTargetWithBlend(
        targetCamera->GetOwner(),
        moveTime,
        EViewTargetBlendFunction::VTBlend_EaseInOut,
        2.0f
    );

    if (returnTime > 0.0f && previousViewTarget)
    {
        GetWorldTimerManager().SetTimer(
            cameraReturnTimer,
            [this]()
            {
                if (previousViewTarget)
                {
                    SetViewTargetWithBlend(
                        previousViewTarget,
                        1.5f,
                        EViewTargetBlendFunction::VTBlend_EaseInOut,
                        2.0f
                    );

                    previousViewTarget = nullptr;
                }
            },
            moveTime + returnTime,
            false
        );
    }
}

