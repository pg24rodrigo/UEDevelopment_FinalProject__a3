// Copyright Rodrigo Ferzuli 2023

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NetShooterCharacter.generated.h"

class ANetBullet;
class UHealthComponent;
UCLASS()
class NETSHOOTER_API ANetShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANetShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	TSubclassOf<ANetBullet> BulletClassToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UHealthComponent> HealthComp;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	UFUNCTION()
	void MoveForward(float value);

	UFUNCTION()
	void MoveRight(float value);

	UFUNCTION(Reliable, Server)
	void NetShoot();

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
};
