// Fill out your copyright notice in the Description page of Project Settings.


#include "Bottun.h"
#include "nyuzuPortfolioCharacter.h"
#include "Door.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABottun::ABottun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;



	player_character = Cast<AnyuzuPortfolioCharacter>(
		UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)
	);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Button"));
}

// Called when the game starts or when spawned
void ABottun::BeginPlay()
{
	Super::BeginPlay();
	
	
}

// Called every frame
void ABottun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	look_actor = player_character->GetLookAtActor();

	if (look_actor != nullptr || look_actor == this) {
		Interaction();
	}
}

void ABottun::Interaction() {
	target = Cast<ADoor>(target);

	if (target != nullptr)
	{
		target->Open();
	}
}