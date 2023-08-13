// Copyright Rodrigo Ferzuli 2023


#include "NetShooterController.h"


// Sets default values
ANetShooterController::ANetShooterController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ANetShooterController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANetShooterController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ANetShooterController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if(!IsValid(InputComponent))
	{
		return;
	}

	InputComponent->BindAxis("LookHorizontal", this, &ThisClass::LookHorizontal);
	InputComponent->BindAxis("LookVertical", this, &ThisClass::LookVertical);
}

void ANetShooterController::LookHorizontal(float value)
{
	AddYawInput(value);
}

void ANetShooterController::LookVertical(float value)
{
	AddPitchInput(value);
}

