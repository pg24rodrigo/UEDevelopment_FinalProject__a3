// Copyright Rodrigo Ferzuli 2023

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "NetShooterGameMode.generated.h"

UCLASS()
class NETSHOOTER_API ANetShooterGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ANetShooterGameMode();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
