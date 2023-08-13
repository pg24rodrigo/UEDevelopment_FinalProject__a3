// Copyright Rodrigo Ferzuli 2023

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "NetShooterController.generated.h"

UCLASS()
class NETSHOOTER_API ANetShooterController : public APlayerController
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ANetShooterController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void SetupInputComponent() override;

protected:

	UFUNCTION()
	void LookHorizontal(float value);

	UFUNCTION()
	void LookVertical(float value);
};
