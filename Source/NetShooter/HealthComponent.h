// Copyright Rodrigo Ferzuli 2023

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHealthChanged);
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class NETSHOOTER_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UHealthComponent();

	UFUNCTION()
	void UpdateHealth(const float& delta);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(ReplicatedUsing = OnRep_Health, BlueprintReadOnly, VisibleAnywhere)
	float Health;

	UPROPERTY(EditAnywhere)
	float MaxHealth;

	UFUNCTION()
	void OnRep_Health();

	UFUNCTION(BlueprintImplementableEvent)
	void HealthChangedVfx();

	UPROPERTY(BlueprintAssignable, BlueprintReadOnly)
	FHealthChanged OnHealthChanged;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
