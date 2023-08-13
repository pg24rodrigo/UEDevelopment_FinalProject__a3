// Copyright Rodrigo Ferzuli 2023

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NetBullet.generated.h"

class UStaticMeshComponent;
class USphereComponent;
class UProjectileMovementComponent;
UCLASS()
class NETSHOOTER_API ANetBullet : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ANetBullet();

protected:
	
	UFUNCTION()
	void OnBulletOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	TObjectPtr<USphereComponent> Collider;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	TObjectPtr<UStaticMeshComponent> BulletMesh;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComp;

	UPROPERTY(EditDefaultsOnly)
	float DamageAmount;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};