// Copyright Rodrigo Ferzuli 2023


#include "HealthComponent.h"

#include "Net/UnrealNetwork.h"


// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	Health = MaxHealth;
	// ...
}

void UHealthComponent::UpdateHealth(const float& delta)
{
	Health -= delta;
	Health = FMath::Clamp(Health, 0.0f, MaxHealth);

	OnRep_Health();

	UE_LOG(LogActor, Display, TEXT("Current Health = %f"), Health);

	if (FMath::IsNearlyZero(Health))
	{
		GetOwner()->Destroy();
	}
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	
	Health = MaxHealth;

	// ...
	
}

void UHealthComponent::OnRep_Health()
{
	HealthChangedVfx();
	OnHealthChanged.Broadcast();
}

// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                     FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UHealthComponent, Health);
}


