// Copyright Epic Games, Inc. All Rights Reserved.


#include "nyuzuPortfolioPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "InputMappingContext.h"
#include "nyuzuPortfolioCameraManager.h"
#include "Blueprint/UserWidget.h"
#include "TimerManager.h"
#include "nyuzuPortfolio.h"
#include "MainHUD.h"
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


void AnyuzuPortfolioPlayerController::ChangeCamera(AActor* NewViewTarget, float BlendTime, float HoldTime, float ReturnBlendTime)
{
	if (!IsValid(NewViewTarget))
	{
		return;
	}

	FTimerManager& TimerManager = GetWorldTimerManager();
	TimerManager.ClearTimer(CameraReturnTimer);

	// 演出中に再度呼ばれた場合、戻り先を演出用カメラで上書きしない
	if (!PreviousViewTarget.IsValid())
	{
		PreviousViewTarget = GetViewTarget();
	}

	// 操作をロック
	SetIgnoreMoveInput(true);
	SetIgnoreLookInput(true);


	//UIの非表示
	AMainHUD* MainHUD = GetHUD<AMainHUD>();

	if (IsValid(MainHUD))
	{
		MainHUD->SetUIVisibility(EHUDType::InGame, false);
	}

	SetViewTargetWithBlend(NewViewTarget, BlendTime, EViewTargetBlendFunction::VTBlend_EaseInOut, 2.0f);

	if (HoldTime > 0.0f)
	{
		// CreateUObject なので、PlayerController が破棄されていれば呼ばれない
		TimerManager.SetTimer(
			CameraReturnTimer,
			[this, ReturnBlendTime, HoldTime]()
			{
				ReturnToDefaultCamera(ReturnBlendTime, HoldTime);
			},
			BlendTime + HoldTime,
			false
		);
	}
}

void AnyuzuPortfolioPlayerController::ReturnToDefaultCamera(float BlendTime, float HoldTime)
{
	FTimerManager& TimerManager = GetWorldTimerManager();
	GetWorldTimerManager().ClearTimer(CameraReturnTimer);

	// 戻り先が消えていたら自分の Pawn に戻す
	AActor* ReturnTarget = PreviousViewTarget.IsValid() ? PreviousViewTarget.Get() : GetPawn();


	if (ReturnTarget)
	{
		SetViewTargetWithBlend(ReturnTarget, BlendTime, EViewTargetBlendFunction::VTBlend_EaseInOut, 2.0f);
	}

	TimerManager.SetTimer(
		CameraReturnTimer,
		[this]()
		{
			//操作をアンロック
			SetIgnoreMoveInput(false);
			SetIgnoreLookInput(false);

			//UIの表示
			AMainHUD* MainHUD = GetHUD<AMainHUD>();
			MainHUD->SetUIVisibility(EHUDType::InGame, true);
		},
		BlendTime,
		false
	);

	PreviousViewTarget = nullptr;
}