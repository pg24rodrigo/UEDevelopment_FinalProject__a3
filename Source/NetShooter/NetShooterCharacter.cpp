// Copyright Rodrigo Ferzuli 2023


#include "NetShooterCharacter.h"

#include "HealthComponent.h"
#include "NetBullet.h"


// Sets default values
ANetShooterCharacter::ANetShooterCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HealthComp = CreateDefaultSubobject<UHealthComponent>(TEXT("Test"));
}

// Called when the game starts or when spawned
void ANetShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANetShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ANetShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (!IsValid(PlayerInputComponent))
	{
		return;
	}
	
	PlayerInputComponent->BindAxis("ForwardMovement", this, &ThisClass::MoveForward);
	PlayerInputComponent->BindAxis("RightMovement", this, &ANetShooterCharacter::MoveRight);
	PlayerInputComponent->BindAction("NetJump", IE_Pressed, this, &ThisClass::Jump);
	PlayerInputComponent->BindAction("NetShoot", IE_Pressed, this, &ThisClass::NetShoot);
}

void ANetShooterCharacter::MoveForward(float value)
{
	if (!IsValid(Controller))
	{
		return;
	}
	
	const FRotator conRotation = Controller->GetControlRotation();
	const FVector direction = FRotationMatrix(conRotation).GetScaledAxis(EAxis::X);
	AddMovementInput(direction, value);
}

void ANetShooterCharacter::MoveRight(float value)
{
	if (!IsValid(Controller))
	{
		return;
	}
	
	const FRotator conRotation = Controller->GetControlRotation();
	const FVector direction = FRotationMatrix(conRotation).GetScaledAxis(EAxis::Y);
	AddMovementInput(direction, value);
}

float ANetShooterCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent,
	AController* EventInstigator, AActor* DamageCauser)
{
	const float returnValue = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (!IsValid(HealthComp))
	{
		return returnValue;
	}

	HealthComp->UpdateHealth(DamageAmount);
	return returnValue;
	
}

void ANetShooterCharacter::NetShoot_Implementation()
{
	if(!IsValid(BulletClassToSpawn))
	{
		return;
	}
	
	FActorSpawnParameters shootParams;
	shootParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	const FRotator spawnRotation = GetControlRotation();
	const FVector spawnLocation = GetActorLocation() + GetControlRotation().Vector() * 50.0f;

	const TObjectPtr<UWorld> world = GetWorld();

	if (!IsValid(world))
	{
		return;
	}

	world->SpawnActor<ANetBullet>(BulletClassToSpawn, spawnLocation, spawnRotation, shootParams);
}

