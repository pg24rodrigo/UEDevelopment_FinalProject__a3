// Copyright Rodrigo Ferzuli 2023


#include "NetBullet.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ANetBullet::ANetBullet()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bullet Mesh"));
	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));

	SetRootComponent(Collider);

	BulletMesh->SetupAttachment(RootComponent);

	Collider->SetSphereRadius(15.0f);

	// Init:
	ProjectileMovementComp->SetUpdatedComponent(RootComponent);
	ProjectileMovementComp->InitialSpeed = 3000.0f;
	ProjectileMovementComp->MaxSpeed = 4000.0f;
	ProjectileMovementComp->bRotationFollowsVelocity = true;
	ProjectileMovementComp->ProjectileGravityScale = 0.0f;

	SetLifeSpan(3.0f);

	DamageAmount = 10.0f;

	SetReplicates(true);
	SetReplicateMovement(true);
	bNetLoadOnClient = true;

}

void ANetBullet::OnBulletOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// getting the actor hit
	const TObjectPtr<AActor> actorHit = SweepResult.GetActor();

	if(!IsValid(actorHit))
	{
		// inbuilt function:
		UGameplayStatics::ApplyDamage(actorHit, DamageAmount, nullptr,  this, UDamageType::StaticClass());
	}
}

// Called when the game starts or when spawned
void ANetBullet::BeginPlay()
{
	Super::BeginPlay();
	Collider->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnBulletOverlap);
}

// Called every frame
void ANetBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

