// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjBase.h"

// Sets default values
AObjBase::AObjBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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
	
}

// Called every frame
void AObjBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AObjBase::SetObjectActive(bool active) {

}

void AObjBase::InitializeObject() {

}
