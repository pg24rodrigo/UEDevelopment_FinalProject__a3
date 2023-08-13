// Copyright Rodrigo Ferzuli 2023


#include "NetShooterGameMode.h"


// Sets default values
ANetShooterGameMode::ANetShooterGameMode()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ANetShooterGameMode::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANetShooterGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

