// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjBase.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AObjBase::AObjBase()
{
 	// 基本は Tick しない。必要なクラスだけ有効にする
	PrimaryActorTick.bCanEverTick = false;

	//見た目の設定
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = SceneRoot;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(SceneRoot);
}

// Called when the game starts or when spawned
void AObjBase::BeginPlay()
{
	Super::BeginPlay();

	InitializeObject();
	
}

void AObjBase::InitializeObject()
{
	//エディタで設定した有効・無効状態を反映する
	SetObjectActive(bIsActive);
}

void AObjBase::SetObjectActive(bool bNewActive) {
		bIsActive = bNewActive;

		SetActorHiddenInGame(!bIsActive);
		SetActorEnableCollision(bIsActive);
}

UStaticMeshComponent* AObjBase::GetMeshComponent() const {
	return MeshComponent;
}